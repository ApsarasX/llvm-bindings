#include "IR/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
// class AllocaInst
//===----------------------------------------------------------------------===//

void AllocaInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "AllocaInst", {
            InstanceMethod("getAllocatedType", &AllocaInst::getAllocatedType),
            InstanceMethod("getArraySize", &AllocaInst::getArraySize),
            InstanceMethod("getType", &AllocaInst::getType),
            InstanceMethod("setDebugLoc", &AllocaInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("AllocaInst", func);
}

Napi::Object AllocaInst::New(Napi::Env env, llvm::AllocaInst *allocaInst) {
    return constructor.New({Napi::External<llvm::AllocaInst>::New(env, allocaInst)});
}

bool AllocaInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::AllocaInst *AllocaInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

AllocaInst::AllocaInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::AllocaInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::AllocaInst>>();
    allocaInst = external.Data();
}

llvm::AllocaInst *AllocaInst::getLLVMPrimitive() {
    return allocaInst;
}

Napi::Value AllocaInst::getAllocatedType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), allocaInst->getAllocatedType());
}

Napi::Value AllocaInst::getArraySize(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), allocaInst->getArraySize());
}

Napi::Value AllocaInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = allocaInst->getType();
    return Type::New(env, type);
}

void AllocaInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        allocaInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::AllocaInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class LoadInst
//===----------------------------------------------------------------------===//

void LoadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "LoadInst", {
            InstanceMethod("getType", &LoadInst::getType),
            InstanceMethod("setDebugLoc", &LoadInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("LoadInst", func);
}

Napi::Object LoadInst::New(Napi::Env env, llvm::LoadInst *loadInst) {
    return constructor.New({Napi::External<llvm::LoadInst>::New(env, loadInst)});
}

bool LoadInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::LoadInst *LoadInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

LoadInst::LoadInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::LoadInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::LoadInst>>();
    loadInst = external.Data();
}

llvm::LoadInst *LoadInst::getLLVMPrimitive() {
    return loadInst;
}

Napi::Value LoadInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = loadInst->getType();
    return Type::New(env, type);
}

void LoadInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        loadInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::LoadInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class StoreInst
//===----------------------------------------------------------------------===//

void StoreInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StoreInst", {
            InstanceMethod("getValueOperand", &StoreInst::getValueOperand),
            InstanceMethod("getPointerOperand", &StoreInst::getPointerOperand),
            InstanceMethod("getPointerOperandType", &StoreInst::getPointerOperandType),
            InstanceMethod("setDebugLoc", &StoreInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("StoreInst", func);
}

Napi::Object StoreInst::New(Napi::Env env, llvm::StoreInst *branchInst) {
    return constructor.New({Napi::External<llvm::StoreInst>::New(env, branchInst)});
}

bool StoreInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::StoreInst *StoreInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

StoreInst::StoreInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StoreInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::StoreInst>>();
    storeInst = external.Data();
}

llvm::StoreInst *StoreInst::getLLVMPrimitive() {
    return storeInst;
}

Napi::Value StoreInst::getValueOperand(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), storeInst->getValueOperand());
}

Napi::Value StoreInst::getPointerOperand(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), storeInst->getPointerOperand());
}

Napi::Value StoreInst::getPointerOperandType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), storeInst->getPointerOperandType());
}

void StoreInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        storeInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::StoreInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class GetElementPtrInst
//===----------------------------------------------------------------------===//

void GetElementPtrInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "GetElementPtrInst", {
            InstanceMethod("getType", &GetElementPtrInst::getType),
            InstanceMethod("setDebugLoc", &GetElementPtrInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("GetElementPtrInst", func);
}

Napi::Object GetElementPtrInst::New(Napi::Env env, llvm::GetElementPtrInst *gepInst) {
    return constructor.New({Napi::External<llvm::GetElementPtrInst>::New(env, gepInst)});
}

bool GetElementPtrInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::GetElementPtrInst *GetElementPtrInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

GetElementPtrInst::GetElementPtrInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::GetElementPtrInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::GetElementPtrInst>>();
    gepInst = external.Data();
}

llvm::GetElementPtrInst *GetElementPtrInst::getLLVMPrimitive() {
    return gepInst;
}

Napi::Value GetElementPtrInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = gepInst->getType();
    return Type::New(env, type);
}

void GetElementPtrInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        gepInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::GetElementPtrInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class CallInst
//===----------------------------------------------------------------------===//

void CallInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CallInst", {
            InstanceMethod("setDebugLoc", &CallInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CallInst", func);
}

Napi::Object CallInst::New(Napi::Env env, llvm::CallInst *callInst) {
    return constructor.New({Napi::External<llvm::CallInst>::New(env, callInst)});
}

bool CallInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CallInst *CallInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CallInst::CallInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CallInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CallInst>>();
    callInst = external.Data();
}

llvm::CallInst *CallInst::getLLVMPrimitive() {
    return callInst;
}

void CallInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        callInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CallInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class PHINode
//===----------------------------------------------------------------------===//

void PHINode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PHINode", {
            InstanceMethod("addIncoming", &PHINode::addIncoming),
            InstanceMethod("setDebugLoc", &PHINode::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("PHINode", func);
}

Napi::Object PHINode::New(Napi::Env env, llvm::PHINode *phiNode) {
    return constructor.New({Napi::External<llvm::PHINode>::New(env, phiNode)});
}

bool PHINode::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::PHINode *PHINode::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

PHINode::PHINode(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PHINode::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::PHINode>>();
    phiNode = external.Data();
}

llvm::PHINode *PHINode::getLLVMPrimitive() {
    return phiNode;
}

void PHINode::addIncoming(const Napi::CallbackInfo &info) {
    if (info.Length() >= 2 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::BasicBlock *basicBlock = BasicBlock::Extract(info[1]);
        phiNode->addIncoming(value, basicBlock);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::PHINode::addIncoming);
}

void PHINode::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        phiNode->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::PHINode::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class LandingPadInst
//===----------------------------------------------------------------------===//

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
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::LandingPadInst *LandingPadInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
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

//===----------------------------------------------------------------------===//
// class ReturnInst
//===----------------------------------------------------------------------===//

void ReturnInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ReturnInst", {
            InstanceMethod("getReturnValue", &ReturnInst::getReturnValue),
            InstanceMethod("setDebugLoc", &ReturnInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ReturnInst", func);
}

Napi::Object ReturnInst::New(Napi::Env env, llvm::ReturnInst *returnInst) {
    return constructor.New({Napi::External<llvm::ReturnInst>::New(env, returnInst)});
}

bool ReturnInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ReturnInst *ReturnInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ReturnInst::ReturnInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ReturnInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ReturnInst>>();
    returnInst = external.Data();
}

llvm::ReturnInst *ReturnInst::getLLVMPrimitive() {
    return returnInst;
}

Napi::Value ReturnInst::getReturnValue(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), returnInst->getReturnValue());
}

void ReturnInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        returnInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ReturnInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class BranchInst
//===----------------------------------------------------------------------===//

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
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::BranchInst *BranchInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
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

//===----------------------------------------------------------------------===//
// class SwitchInst
//===----------------------------------------------------------------------===//

void SwitchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SwitchInst", {
            InstanceMethod("addCase", &SwitchInst::addCase),
            InstanceMethod("setDebugLoc", &SwitchInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("SwitchInst", func);
}

Napi::Object SwitchInst::New(Napi::Env env, llvm::SwitchInst *switchInst) {
    return constructor.New({Napi::External<llvm::SwitchInst>::New(env, switchInst)});
}

bool SwitchInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SwitchInst *SwitchInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SwitchInst::SwitchInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SwitchInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::SwitchInst>>();
    switchInst = external.Data();
}

llvm::SwitchInst *SwitchInst::getLLVMPrimitive() {
    return switchInst;
}

void SwitchInst::addCase(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen >= 2 && ConstantInt::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1])) {
        llvm::ConstantInt *onVal = ConstantInt::Extract(info[0]);
        llvm::BasicBlock *dest = BasicBlock::Extract(info[1]);
        switchInst->addCase(onVal, dest);
    } else {
        throw Napi::TypeError::New(env, ErrMsg::Class::SwitchInst::addCase);
    }
}

void SwitchInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        switchInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SwitchInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
// class InvokeInst
//===----------------------------------------------------------------------===//

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
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
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

//===----------------------------------------------------------------------===//
// class ResumeInst
//===----------------------------------------------------------------------===//

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
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ResumeInst *ResumeInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
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

//===----------------------------------------------------------------------===//
// class UnreachableInst
//===----------------------------------------------------------------------===//

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
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::UnreachableInst *UnreachableInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
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
