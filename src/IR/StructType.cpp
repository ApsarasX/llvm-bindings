#include "IR/StructType.h"
#include "IR/Type.h"
#include "Util/Inherit.h"

void StructType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StructType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("StructType", func);
}

Napi::Object StructType::New(Napi::Env env, llvm::StructType *type) {
    return constructor.New({Napi::External<llvm::StructType>::New(env, type)});
}

bool StructType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::StructType *StructType::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

StructType::StructType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "StructType Constructor needs to be called with new");
    }
    if (info.Length() < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected struct type pointer");
    }
    auto external = info[0].As<Napi::External<llvm::StructType>>();
    structType = external.Data();
}


llvm::StructType *StructType::getLLVMPrimitive() {
    return structType;
}
