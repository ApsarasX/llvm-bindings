#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>

#include "IR/Value.h"
#include "IR/Type.h"
#include "IR/BasicBlock.h"
#include "IR/User.h"

void Value::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Value", {
            InstanceMethod("hasName", &Value::hasName),
            InstanceMethod("getType", &Value::getType),
            InstanceMethod("getName", &Value::getName),
            InstanceMethod("setName", &Value::setName),
            InstanceMethod("release", &Value::deleteValue),
            InstanceMethod("deleteValue", &Value::deleteValue),
            InstanceMethod("replaceAllUsesWith", &Value::replaceAllUsesWith),
            InstanceMethod("use_empty", &Value::useEmpty),
            StaticValue("MaxAlignmentExponent", Napi::Number::New(env, llvm::Value::MaxAlignmentExponent)),
            StaticValue("MaximumAlignment", Napi::Number::New(env, llvm::Value::MaximumAlignment))
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Value", func);
}


Napi::Value Value::New(Napi::Env env, llvm::Value *value) {
    if (llvm::BasicBlock::classof(value)) {
        return BasicBlock::New(env, static_cast<llvm::BasicBlock *>(value));
    } else if (llvm::User::classof(value)) {
        return User::New(env, static_cast<llvm::User *>(value));
    }
    return constructor.New({Napi::External<llvm::Value>::New(env, value)});
}

bool Value::IsClassOf(Napi::Value value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Value *Value::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Value::Value(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Class Constructor Value cannot be invoked without new");
    }
    if (info.Length() != 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "External Value Pointer required");
    }
    auto external = info[0].As<Napi::External<llvm::Value>>();
    value = external.Data();
}

Napi::Value Value::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = value->getType();
    return Type::New(env, type);
}

Napi::Value Value::hasName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, value->hasName());
}

Napi::Value Value::getName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, value->getName().str());
}

void Value::setName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "name needs to be a string");
    }
    const std::string &name = info[0].As<Napi::String>();
    value->setName(name);
}

void Value::deleteValue(const Napi::CallbackInfo &info) {
    value->deleteValue();
}

void Value::replaceAllUsesWith(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !Value::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "replaceAllUsesWith needs to be called with: value: Value");
    }
    llvm::Value *newValue = Value::Extract(info[0]);
    value->replaceAllUsesWith(newValue);
}

Napi::Value Value::useEmpty(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, value->use_empty());
}

llvm::Value *Value::getLLVMPrimitive() {
    return value;
}
