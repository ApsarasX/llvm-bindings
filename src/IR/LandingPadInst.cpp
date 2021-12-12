#include "IR/IR.h"
#include "Util/Util.h"

void LandingPadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "LandingPadInst", {
            InstanceMethod("setCleanup", &LandingPadInst::setCleanup),
            InstanceMethod("addClause", &LandingPadInst::addClause),
            InstanceMethod("setDebugLoc", &LandingPadInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("LandingPadInst", func);
}

Napi::Object LandingPadInst::New(Napi::Env env, llvm::LandingPadInst *lpInst) {
    return constructor.New({Napi::External<llvm::LandingPadInst>::New(env, lpInst)});
}

bool LandingPadInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::LandingPadInst *LandingPadInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

LandingPadInst::LandingPadInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::LandingPadInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::LandingPadInst>>();
    lpInst = external.Data();
}

llvm::LandingPadInst *LandingPadInst::getLLVMPrimitive() {
    return lpInst;
}

void LandingPadInst::setCleanup(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (info.Length() == 1 && info[0].IsBoolean()) {
        lpInst->setCleanup(info[0].As<Napi::Boolean>());
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::LandingPadInst::setCleanup);
}

void LandingPadInst::addClause(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (info.Length() == 1 && Constant::IsClassOf(info[0])) {
        lpInst->addClause(Constant::Extract(info[0]));
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::LandingPadInst::addClause);
}

void LandingPadInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        lpInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::LandingPadInst::setDebugLoc);
}