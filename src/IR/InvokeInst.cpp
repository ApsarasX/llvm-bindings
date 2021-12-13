#include "IR/IR.h"
#include "Util/Util.h"

void InvokeInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "InvokeInst", {
            InstanceMethod("setDebugLoc", &InvokeInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("InvokeInst", func);
}

Napi::Object InvokeInst::New(Napi::Env env, llvm::InvokeInst *invokeInst) {
    return constructor.New({Napi::External<llvm::InvokeInst>::New(env, invokeInst)});
}

bool InvokeInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::InvokeInst *InvokeInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

InvokeInst::InvokeInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::InvokeInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::InvokeInst>>();
    invokeInst = external.Data();
}

llvm::InvokeInst *InvokeInst::getLLVMPrimitive() {
    return invokeInst;
}

void InvokeInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        invokeInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::InvokeInst::setDebugLoc);
}