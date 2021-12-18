#include "IR/index.h"
#include "Util/index.h"

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
            InstanceMethod("user_empty", &Value::userEmpty),
            StaticValue("MaxAlignmentExponent", Napi::Number::New(env, llvm::Value::MaxAlignmentExponent)),
            StaticValue("MaximumAlignment", Napi::Number::New(env, llvm::Value::MaximumAlignment))
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Value", func);
}

Napi::Value Value::New(Napi::Env env, llvm::Value *value) {
    if (llvm::isa<llvm::Argument>(value)) {
        return Argument::New(env, llvm::cast<llvm::Argument>(value));
    } else if (llvm::isa<llvm::BasicBlock>(value)) {
        return BasicBlock::New(env, llvm::cast<llvm::BasicBlock>(value));
    } else if (llvm::isa<llvm::User>(value)) {
        return User::New(env, llvm::cast<llvm::User>(value));
    }
    return constructor.New({Napi::External<llvm::Value>::New(env, value)});
}

bool Value::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Value *Value::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Value::Value(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Value::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Value>>();
    value = external.Data();
}

llvm::Value *Value::getLLVMPrimitive() {
    return value;
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
    if (info.Length() == 0 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Value::setName);
    }
    const std::string &name = info[0].As<Napi::String>();
    value->setName(name);
}

void Value::deleteValue(const Napi::CallbackInfo &info) {
    value->deleteValue();
}

void Value::replaceAllUsesWith(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Value::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Value::replaceAllUsesWith);
    }
    llvm::Value *newValue = Value::Extract(info[0]);
    value->replaceAllUsesWith(newValue);
}

Napi::Value Value::useEmpty(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), value->use_empty());
}

Napi::Value Value::userEmpty(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), value->user_empty());
}
