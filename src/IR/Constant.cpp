#include "IR/IR.h"
#include "Util/Util.h"

void Constant::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Constant", {
            StaticMethod("getNullValue", Constant::getNullValue),
            StaticMethod("getAllOnesValue", Constant::getAllOnesValue),
            InstanceMethod("isNullValue", &Constant::isNullValue),
            InstanceMethod("isOneValue", &Constant::isOneValue),
            InstanceMethod("isAllOnesValue", &Constant::isAllOnesValue)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), User::constructor.Value());
    exports.Set("Constant", func);
}

Napi::Object Constant::New(Napi::Env env, llvm::Constant *constant) {
    if (llvm::GlobalValue::classof(constant)) {
        return GlobalValue::New(env, static_cast<llvm::GlobalValue *>(constant));
    } else if (llvm::ConstantInt::classof(constant)) {
        return ConstantInt::New(env, static_cast<llvm::ConstantInt *>(constant));
    } else if (llvm::ConstantFP::classof(constant)) {
        return ConstantFP::New(env, static_cast<llvm::ConstantFP *>(constant));
    } else if (llvm::ConstantPointerNull::classof(constant)) {
        return ConstantPointerNull::New(env, static_cast<llvm::ConstantPointerNull *>(constant));
    }
    return constructor.New({Napi::External<llvm::Constant>::New(env, constant)});
}

bool Constant::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Constant *Constant::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Constant::Constant(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Constant>>();
    constant = external.Data();
}

Napi::Value Constant::getNullValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Type::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::getNullValue);
    }
    llvm::Type *type = Type::Extract(info[0]);
    llvm::Constant *constant = llvm::Constant::getNullValue(type);
    return Constant::New(env, constant);
}

Napi::Value Constant::getAllOnesValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Type::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::getAllOnesValue);
    }
    llvm::Type *type = Type::Extract(info[0]);
    llvm::Constant *constant = llvm::Constant::getAllOnesValue(type);
    return Constant::New(env, constant);
}

Napi::Value Constant::isNullValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isNullValue());
}

Napi::Value Constant::isOneValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isOneValue());
}

Napi::Value Constant::isAllOnesValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isAllOnesValue());
}

llvm::Constant *Constant::getLLVMPrimitive() {
    return constant;
}