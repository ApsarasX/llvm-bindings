#include "IR/IR.h"
#include "Util/Util.h"

void ResumeInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ResumeInst", {
            InstanceMethod("setDebugLoc", &ResumeInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ResumeInst", func);
}

Napi::Object ResumeInst::New(Napi::Env env, llvm::ResumeInst *resumeInst) {
    return constructor.New({Napi::External<llvm::ResumeInst>::New(env, resumeInst)});
}

bool ResumeInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ResumeInst *ResumeInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ResumeInst::ResumeInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ResumeInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ResumeInst>>();
    resumeInst = external.Data();
}

llvm::ResumeInst *ResumeInst::getLLVMPrimitive() {
    return resumeInst;
}

void ResumeInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        resumeInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ResumeInst::setDebugLoc);
}