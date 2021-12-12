#include "IR/IR.h"
#include "Util/Util.h"

void DIType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DIType", func);
}

Napi::Value DIType::New(Napi::Env env, llvm::DIType *type) {
    if (llvm::isa<llvm::DIBasicType>(type)) {
        return DIBasicType::New(env, llvm::cast<llvm::DIBasicType>(type));
    } else if (llvm::isa<llvm::DISubroutineType>(type)) {
        return DISubroutineType::New(env, llvm::cast<llvm::DISubroutineType>(type));
    }
    return constructor.New({Napi::External<llvm::DIType>::New(env, type)});
}

bool DIType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIType *DIType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIType::DIType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIType>>();
    type = external.Data();
}

llvm::DIType *DIType::getLLVMPrimitive() {
    return type;
}