#include "IR/IR.h"
#include "Util/Util.h"

void DISubroutineType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DISubroutineType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DISubroutineType", func);
}

Napi::Value DISubroutineType::New(Napi::Env env, llvm::DISubroutineType *type) {
    return constructor.New({Napi::External<llvm::DISubroutineType>::New(env, type)});
}

bool DISubroutineType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DISubroutineType *DISubroutineType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DISubroutineType::DISubroutineType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DISubroutineType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DISubroutineType>>();
    type = external.Data();
}

llvm::DISubroutineType *DISubroutineType::getLLVMPrimitive() {
    return type;
}