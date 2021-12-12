#include "IR/IR.h"
#include "Util/Util.h"

void BranchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "BranchInst", {
            InstanceMethod("isUnconditional", &BranchInst::isUnconditional),
            InstanceMethod("isConditional", &BranchInst::isConditional),
            InstanceMethod("getCondition", &BranchInst::getCondition),
            InstanceMethod("getNumSuccessors", &BranchInst::getNumSuccessors),
            InstanceMethod("getSuccessor", &BranchInst::getSuccessor),
            InstanceMethod("setDebugLoc", &BranchInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("BranchInst", func);
}

Napi::Object BranchInst::New(Napi::Env env, llvm::BranchInst *branchInst) {
    return constructor.New({Napi::External<llvm::BranchInst>::New(env, branchInst)});
}

bool BranchInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::BranchInst *BranchInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

BranchInst::BranchInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::BranchInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::BranchInst>>();
    branchInst = external.Data();
}

llvm::BranchInst *BranchInst::getLLVMPrimitive() {
    return branchInst;
}

Napi::Value BranchInst::isUnconditional(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), branchInst->isUnconditional());
}

Napi::Value BranchInst::isConditional(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), branchInst->isConditional());
}

Napi::Value BranchInst::getCondition(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), branchInst->getCondition());
}

Napi::Value BranchInst::getNumSuccessors(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), branchInst->getNumSuccessors());
}

Napi::Value BranchInst::getSuccessor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && info[0].IsNumber()) {
        unsigned i = info[0].As<Napi::Number>();
        llvm::BasicBlock *successor = branchInst->getSuccessor(i);
        return BasicBlock::New(env, successor);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::BranchInst::getSuccessor);
}

void BranchInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        branchInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::BranchInst::setDebugLoc);
}