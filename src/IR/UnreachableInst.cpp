#include "IR/IR.h"
#include "Util/Util.h"

void UnreachableInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "UnreachableInst", {
            InstanceMethod("setDebugLoc", &UnreachableInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("UnreachableInst", func);
}

Napi::Object UnreachableInst::New(Napi::Env env, llvm::UnreachableInst *unreachableInst) {
    return constructor.New({Napi::External<llvm::UnreachableInst>::New(env, unreachableInst)});
}

bool UnreachableInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::UnreachableInst *UnreachableInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

UnreachableInst::UnreachableInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::UnreachableInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::UnreachableInst>>();
    unreachableInst = external.Data();
}

llvm::UnreachableInst *UnreachableInst::getLLVMPrimitive() {
    return unreachableInst;
}

void UnreachableInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        unreachableInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::UnreachableInst::setDebugLoc);
}