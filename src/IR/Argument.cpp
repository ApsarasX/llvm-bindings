#include "IR/index.h"
#include "Util/index.h"

void Argument::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Argument", {
            InstanceMethod("getParent", &Argument::getParent),
            InstanceMethod("getArgNo", &Argument::getArgNo),
            InstanceMethod("setName", &Argument::setName)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Value::constructor.Value());
    exports.Set("Argument", func);
}

Napi::Object Argument::New(Napi::Env env, llvm::Argument *argument) {
    return constructor.New({Napi::External<llvm::Argument>::New(env, argument)});
}

bool Argument::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Argument *Argument::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Argument::Argument(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (!info.IsConstructCall() ||
        argsLen == 0 ||
        !info[0].IsExternal() && !Type::IsClassOf(info[0]) ||
        argsLen >= 2 && !info[1].IsString() ||
        argsLen >= 3 && !Function::IsClassOf(info[2]) ||
        argsLen >= 4 && !info[3].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Argument::constructor);
    }
    if (argsLen >= 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::Argument>>();
        argument = external.Data();
        return;
    }
    llvm::Type *type = Type::Extract(info[0]);
    std::string name;
    llvm::Function *func = nullptr;
    unsigned argNo = 0;
    if (argsLen >= 2) {
        name = info[1].As<Napi::String>();
    }
    if (argsLen >= 3) {
        func = Function::Extract(info[2]);
    }
    if (argsLen >= 4) {
        argNo = info[3].As<Napi::Number>();
    }
    argument = new llvm::Argument(type, name, func, argNo);
}

llvm::Argument *Argument::getLLVMPrimitive() {
    return argument;
}

Napi::Value Argument::getParent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Function::New(env, argument->getParent());
}

Napi::Value Argument::getArgNo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, argument->getArgNo());
}

void Argument::setName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Argument::setName);
    }
    const std::string &name = info[0].As<Napi::String>();
    argument->setName(name);
}
