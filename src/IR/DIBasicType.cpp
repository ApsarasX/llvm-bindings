#include "IR/IR.h"
#include "Util/Util.h"

void DIBasicType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIBasicType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DIBasicType", func);
}

Napi::Value DIBasicType::New(Napi::Env env, llvm::DIBasicType *type) {
    return constructor.New({Napi::External<llvm::DIBasicType>::New(env, type)});
}

bool DIBasicType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIBasicType *DIBasicType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIBasicType::DIBasicType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIBasicType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIBasicType>>();
    type = external.Data();
}

llvm::DIBasicType *DIBasicType::getLLVMPrimitive() {
    return type;
}