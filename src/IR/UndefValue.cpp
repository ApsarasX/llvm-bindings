#include "IR/IR.h"
#include "Util/Util.h"

void UndefValue::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "UndefValue", {
            StaticMethod("get", &UndefValue::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("UndefValue", func);
}

Napi::Object UndefValue::New(Napi::Env env, llvm::UndefValue *undefValue) {
    return constructor.New({Napi::External<llvm::UndefValue>::New(env, undefValue)});
}

bool UndefValue::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::UndefValue *UndefValue::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

UndefValue::UndefValue(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::UndefValue::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::UndefValue >>();
    undefValue = external.Data();
}

llvm::UndefValue *UndefValue::getLLVMPrimitive() {
    return undefValue;
}

Napi::Value UndefValue::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && Type::IsClassOf(info[0])) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::UndefValue *undefValue = llvm::UndefValue::get(type);
        return UndefValue::New(env, undefValue);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::UndefValue::get);
}
