#include "IR/IR.h"
#include "Util/Util.h"

void DebugLoc::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DebugLoc", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("DebugLoc", func);
}

Napi::Value DebugLoc::New(Napi::Env env, llvm::DebugLoc *location) {
    return constructor.New({Napi::External<llvm::DebugLoc>::New(env, location)});
}

bool DebugLoc::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DebugLoc *DebugLoc::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DebugLoc::DebugLoc(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 0 && info.IsConstructCall()) {
        location = new llvm::DebugLoc();
        return;
    } else if (argsLen == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::DebugLoc>>();
        location = external.Data();
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DebugLoc::constructor);
}

llvm::DebugLoc *DebugLoc::getLLVMPrimitive() {
    return location;
}