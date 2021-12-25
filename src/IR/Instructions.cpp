#include "IR/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
//                        AllocaInst Class
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
    llvm::PointerType *type = allocaInst->getType();
    return PointerType::New(env, type);
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
//                        LoadInst Class
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
//                        StoreInst Class
//===----------------------------------------------------------------------===//

void StoreInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StoreInst", {
            InstanceMethod("getValueOperand", &StoreInst::getValueOperand),
            InstanceMethod("getPointerOperand", &StoreInst::getPointerOperand),
            InstanceMethod("getPointerOperandType", &StoreInst::getPointerOperandType),
            InstanceMethod("getType", &StoreInst::getType),
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

Napi::Value StoreInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = storeInst->getType();
    return Type::New(env, type);
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
//                        FenceInst Class
//===----------------------------------------------------------------------===//

void FenceInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FenceInst", {
            InstanceMethod("getType", &FenceInst::getType),
            InstanceMethod("setDebugLoc", &FenceInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FenceInst", func);
}

Napi::Object FenceInst::New(Napi::Env env, llvm::FenceInst *fenceInst) {
    return constructor.New({Napi::External<llvm::FenceInst>::New(env, fenceInst)});
}

bool FenceInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FenceInst *FenceInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FenceInst::FenceInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FenceInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FenceInst>>();
    fenceInst = external.Data();
}

llvm::FenceInst *FenceInst::getLLVMPrimitive() {
    return fenceInst;
}

Napi::Value FenceInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fenceInst->getType();
    return Type::New(env, type);
}

void FenceInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fenceInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FenceInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        AtomicCmpXchgInst Class
//===----------------------------------------------------------------------===//

void AtomicCmpXchgInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "AtomicCmpXchgInst", {
            InstanceMethod("getType", &AtomicCmpXchgInst::getType),
            InstanceMethod("setDebugLoc", &AtomicCmpXchgInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("AtomicCmpXchgInst", func);
}

Napi::Object AtomicCmpXchgInst::New(Napi::Env env, llvm::AtomicCmpXchgInst *atomicCmpXchgInst) {
    return constructor.New({Napi::External<llvm::AtomicCmpXchgInst>::New(env, atomicCmpXchgInst)});
}

bool AtomicCmpXchgInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::AtomicCmpXchgInst *AtomicCmpXchgInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

AtomicCmpXchgInst::AtomicCmpXchgInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::AtomicCmpXchgInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::AtomicCmpXchgInst>>();
    atomicCmpXchgInst = external.Data();
}

llvm::AtomicCmpXchgInst *AtomicCmpXchgInst::getLLVMPrimitive() {
    return atomicCmpXchgInst;
}

Napi::Value AtomicCmpXchgInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = atomicCmpXchgInst->getType();
    return Type::New(env, type);
}

void AtomicCmpXchgInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        atomicCmpXchgInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::AtomicCmpXchgInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        AtomicRMWInst Class
//===----------------------------------------------------------------------===//

void AtomicRMWInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "AtomicRMWInst", {
            InstanceMethod("getType", &AtomicRMWInst::getType),
            InstanceMethod("setDebugLoc", &AtomicRMWInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("AtomicRMWInst", func);
}

Napi::Object AtomicRMWInst::New(Napi::Env env, llvm::AtomicRMWInst *atomicRMWInst) {
    return constructor.New({Napi::External<llvm::AtomicRMWInst>::New(env, atomicRMWInst)});
}

bool AtomicRMWInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::AtomicRMWInst *AtomicRMWInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

AtomicRMWInst::AtomicRMWInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::AtomicRMWInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::AtomicRMWInst>>();
    atomicRMWInst = external.Data();
}

llvm::AtomicRMWInst *AtomicRMWInst::getLLVMPrimitive() {
    return atomicRMWInst;
}

Napi::Value AtomicRMWInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = atomicRMWInst->getType();
    return Type::New(env, type);
}

void AtomicRMWInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        atomicRMWInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::AtomicRMWInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        GetElementPtrInst Class
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
//                        ICmpInst Class
//===----------------------------------------------------------------------===//

void ICmpInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ICmpInst", {
            InstanceMethod("getType", &ICmpInst::getType),
            InstanceMethod("setDebugLoc", &ICmpInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ICmpInst", func);
}

Napi::Object ICmpInst::New(Napi::Env env, llvm::ICmpInst *icmpInst) {
    return constructor.New({Napi::External<llvm::ICmpInst>::New(env, icmpInst)});
}

bool ICmpInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ICmpInst *ICmpInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ICmpInst::ICmpInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ICmpInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ICmpInst>>();
    icmpInst = external.Data();
}

llvm::ICmpInst *ICmpInst::getLLVMPrimitive() {
    return icmpInst;
}

Napi::Value ICmpInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = icmpInst->getType();
    return Type::New(env, type);
}

void ICmpInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        icmpInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ICmpInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FCmpInst Class
//===----------------------------------------------------------------------===//

void FCmpInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FCmpInst", {
            InstanceMethod("getType", &FCmpInst::getType),
            InstanceMethod("setDebugLoc", &FCmpInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FCmpInst", func);
}

Napi::Object FCmpInst::New(Napi::Env env, llvm::FCmpInst *fcmpInst) {
    return constructor.New({Napi::External<llvm::FCmpInst>::New(env, fcmpInst)});
}

bool FCmpInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FCmpInst *FCmpInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FCmpInst::FCmpInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FCmpInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FCmpInst>>();
    fcmpInst = external.Data();
}

llvm::FCmpInst *FCmpInst::getLLVMPrimitive() {
    return fcmpInst;
}

Napi::Value FCmpInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fcmpInst->getType();
    return Type::New(env, type);
}

void FCmpInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fcmpInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FCmpInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        CallInst Class
//===----------------------------------------------------------------------===//

void CallInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CallInst", {
            InstanceMethod("getType", &CallInst::getType),
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

Napi::Value CallInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = callInst->getType();
    return Type::New(env, type);
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
//                        SelectInst Class
//===----------------------------------------------------------------------===//

void SelectInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SelectInst", {
            InstanceMethod("getType", &SelectInst::getType),
            InstanceMethod("getCondition", &SelectInst::getCondition),
            InstanceMethod("getTrueValue", &SelectInst::getTrueValue),
            InstanceMethod("getFalseValue", &SelectInst::getFalseValue),
            InstanceMethod("setCondition", &SelectInst::setCondition),
            InstanceMethod("setTrueValue", &SelectInst::setTrueValue),
            InstanceMethod("setFalseValue", &SelectInst::setFalseValue),
            InstanceMethod("setDebugLoc", &SelectInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("SelectInst", func);
}

Napi::Object SelectInst::New(Napi::Env env, llvm::SelectInst *selectInst) {
    return constructor.New({Napi::External<llvm::SelectInst>::New(env, selectInst)});
}

bool SelectInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SelectInst *SelectInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SelectInst::SelectInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SelectInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::SelectInst>>();
    selectInst = external.Data();
}

llvm::SelectInst *SelectInst::getLLVMPrimitive() {
    return selectInst;
}

Napi::Value SelectInst::getCondition(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), selectInst->getCondition());
}

Napi::Value SelectInst::getTrueValue(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), selectInst->getTrueValue());
}

Napi::Value SelectInst::getFalseValue(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), selectInst->getFalseValue());
}

void SelectInst::setCondition(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && Value::IsClassOf(info[0])) {
        llvm::Value *cond = Value::Extract(info[0]);
        selectInst->setCondition(cond);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SelectInst::setCondition);
}

void SelectInst::setTrueValue(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && Value::IsClassOf(info[0])) {
        llvm::Value *cond = Value::Extract(info[0]);
        selectInst->setTrueValue(cond);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SelectInst::setTrueValue);
}

void SelectInst::setFalseValue(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && Value::IsClassOf(info[0])) {
        llvm::Value *cond = Value::Extract(info[0]);
        selectInst->setFalseValue(cond);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SelectInst::setFalseValue);
}

Napi::Value SelectInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = selectInst->getType();
    return Type::New(env, type);
}

void SelectInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        selectInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SelectInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        VAArgInst Class
//===----------------------------------------------------------------------===//

void VAArgInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "VAArgInst", {
            InstanceMethod("getType", &VAArgInst::getType),
            InstanceMethod("setDebugLoc", &VAArgInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("VAArgInst", func);
}

Napi::Object VAArgInst::New(Napi::Env env, llvm::VAArgInst *vaArgInst) {
    return constructor.New({Napi::External<llvm::VAArgInst>::New(env, vaArgInst)});
}

bool VAArgInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::VAArgInst *VAArgInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

VAArgInst::VAArgInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::VAArgInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::VAArgInst>>();
    vaArgInst = external.Data();
}

llvm::VAArgInst *VAArgInst::getLLVMPrimitive() {
    return vaArgInst;
}

Napi::Value VAArgInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = vaArgInst->getType();
    return Type::New(env, type);
}

void VAArgInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        vaArgInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::VAArgInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        ExtractElementInst Class
//===----------------------------------------------------------------------===//

void ExtractElementInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ExtractElementInst", {
            InstanceMethod("getType", &ExtractElementInst::getType),
            InstanceMethod("setDebugLoc", &ExtractElementInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ExtractElementInst", func);
}

Napi::Object ExtractElementInst::New(Napi::Env env, llvm::ExtractElementInst *extractElementInst) {
    return constructor.New({Napi::External<llvm::ExtractElementInst>::New(env, extractElementInst)});
}

bool ExtractElementInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ExtractElementInst *ExtractElementInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ExtractElementInst::ExtractElementInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ExtractElementInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ExtractElementInst>>();
    extractElementInst = external.Data();
}

llvm::ExtractElementInst *ExtractElementInst::getLLVMPrimitive() {
    return extractElementInst;
}

Napi::Value ExtractElementInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = extractElementInst->getType();
    return Type::New(env, type);
}

void ExtractElementInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        extractElementInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ExtractElementInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        InsertElementInst Class
//===----------------------------------------------------------------------===//

void InsertElementInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "InsertElementInst", {
            InstanceMethod("getType", &InsertElementInst::getType),
            InstanceMethod("setDebugLoc", &InsertElementInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("InsertElementInst", func);
}

Napi::Object InsertElementInst::New(Napi::Env env, llvm::InsertElementInst *insertElementInst) {
    return constructor.New({Napi::External<llvm::InsertElementInst>::New(env, insertElementInst)});
}

bool InsertElementInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::InsertElementInst *InsertElementInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

InsertElementInst::InsertElementInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::InsertElementInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::InsertElementInst>>();
    insertElementInst = external.Data();
}

llvm::InsertElementInst *InsertElementInst::getLLVMPrimitive() {
    return insertElementInst;
}

Napi::Value InsertElementInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::VectorType *type = insertElementInst->getType();
    return VectorType::New(env, type);
}

void InsertElementInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        insertElementInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::InsertElementInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        ShuffleVectorInst Class
//===----------------------------------------------------------------------===//

void ShuffleVectorInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ShuffleVectorInst", {
            InstanceMethod("getType", &ShuffleVectorInst::getType),
            InstanceMethod("setDebugLoc", &ShuffleVectorInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ShuffleVectorInst", func);
}

Napi::Object ShuffleVectorInst::New(Napi::Env env, llvm::ShuffleVectorInst *shuffleVectorInst) {
    return constructor.New({Napi::External<llvm::ShuffleVectorInst>::New(env, shuffleVectorInst)});
}

bool ShuffleVectorInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ShuffleVectorInst *ShuffleVectorInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ShuffleVectorInst::ShuffleVectorInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ShuffleVectorInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ShuffleVectorInst>>();
    shuffleVectorInst = external.Data();
}

llvm::ShuffleVectorInst *ShuffleVectorInst::getLLVMPrimitive() {
    return shuffleVectorInst;
}

Napi::Value ShuffleVectorInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::VectorType *type = shuffleVectorInst->getType();
    return VectorType::New(env, type);
}

void ShuffleVectorInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        shuffleVectorInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ShuffleVectorInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        ExtractValueInst Class
//===----------------------------------------------------------------------===//

void ExtractValueInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ExtractValueInst", {
            InstanceMethod("getType", &ExtractValueInst::getType),
            InstanceMethod("setDebugLoc", &ExtractValueInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ExtractValueInst", func);
}

Napi::Object ExtractValueInst::New(Napi::Env env, llvm::ExtractValueInst *extractValueInst) {
    return constructor.New({Napi::External<llvm::ExtractValueInst>::New(env, extractValueInst)});
}

bool ExtractValueInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ExtractValueInst *ExtractValueInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ExtractValueInst::ExtractValueInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ExtractValueInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ExtractValueInst>>();
    extractValueInst = external.Data();
}

llvm::ExtractValueInst *ExtractValueInst::getLLVMPrimitive() {
    return extractValueInst;
}

Napi::Value ExtractValueInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = extractValueInst->getType();
    return Type::New(env, type);
}

void ExtractValueInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        extractValueInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ExtractValueInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        InsertValueInst Class
//===----------------------------------------------------------------------===//

void InsertValueInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "InsertValueInst", {
            InstanceMethod("getType", &InsertValueInst::getType),
            InstanceMethod("setDebugLoc", &InsertValueInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("InsertValueInst", func);
}

Napi::Object InsertValueInst::New(Napi::Env env, llvm::InsertValueInst *insertValueInst) {
    return constructor.New({Napi::External<llvm::InsertValueInst>::New(env, insertValueInst)});
}

bool InsertValueInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::InsertValueInst *InsertValueInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

InsertValueInst::InsertValueInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::InsertValueInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::InsertValueInst>>();
    insertValueInst = external.Data();
}

llvm::InsertValueInst *InsertValueInst::getLLVMPrimitive() {
    return insertValueInst;
}

Napi::Value InsertValueInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = insertValueInst->getType();
    return Type::New(env, type);
}

void InsertValueInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        insertValueInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::InsertValueInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        PHINode Class
//===----------------------------------------------------------------------===//

void PHINode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PHINode", {
            InstanceMethod("addIncoming", &PHINode::addIncoming),
            InstanceMethod("getType", &PHINode::getType),
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

Napi::Value PHINode::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = phiNode->getType();
    return Type::New(env, type);
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
//                        LandingPadInst Class
//===----------------------------------------------------------------------===//

void LandingPadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "LandingPadInst", {
            InstanceMethod("setCleanup", &LandingPadInst::setCleanup),
            InstanceMethod("addClause", &LandingPadInst::addClause),
            InstanceMethod("getType", &LandingPadInst::getType),
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
    if (info.Length() == 1 && info[0].IsBoolean()) {
        lpInst->setCleanup(info[0].As<Napi::Boolean>());
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::LandingPadInst::setCleanup);
}

void LandingPadInst::addClause(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && Constant::IsClassOf(info[0])) {
        lpInst->addClause(Constant::Extract(info[0]));
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::LandingPadInst::addClause);
}

Napi::Value LandingPadInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = lpInst->getType();
    return Type::New(env, type);
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
//                        ReturnInst Class
//===----------------------------------------------------------------------===//

void ReturnInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ReturnInst", {
            InstanceMethod("getReturnValue", &ReturnInst::getReturnValue),
            InstanceMethod("getType", &ReturnInst::getType),
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

Napi::Value ReturnInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = returnInst->getType();
    return Type::New(env, type);
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
//                        BranchInst Class
//===----------------------------------------------------------------------===//

void BranchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "BranchInst", {
            InstanceMethod("isUnconditional", &BranchInst::isUnconditional),
            InstanceMethod("isConditional", &BranchInst::isConditional),
            InstanceMethod("getCondition", &BranchInst::getCondition),
            InstanceMethod("getNumSuccessors", &BranchInst::getNumSuccessors),
            InstanceMethod("getSuccessor", &BranchInst::getSuccessor),
            InstanceMethod("getType", &BranchInst::getType),
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

Napi::Value BranchInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = branchInst->getType();
    return Type::New(env, type);
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
//                        SwitchInst Class
//===----------------------------------------------------------------------===//

void SwitchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SwitchInst", {
            InstanceMethod("addCase", &SwitchInst::addCase),
            InstanceMethod("getType", &SwitchInst::getType),
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

Napi::Value SwitchInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = switchInst->getType();
    return Type::New(env, type);
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
//                        IndirectBrInst Class
//===----------------------------------------------------------------------===//

void IndirectBrInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IndirectBrInst", {
            InstanceMethod("getType", &IndirectBrInst::getType),
            InstanceMethod("setDebugLoc", &IndirectBrInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("IndirectBrInst", func);
}

Napi::Object IndirectBrInst::New(Napi::Env env, llvm::IndirectBrInst *indirectBrInst) {
    return constructor.New({Napi::External<llvm::IndirectBrInst>::New(env, indirectBrInst)});
}

bool IndirectBrInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::IndirectBrInst *IndirectBrInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IndirectBrInst::IndirectBrInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IndirectBrInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::IndirectBrInst>>();
    indirectBrInst = external.Data();
}

llvm::IndirectBrInst *IndirectBrInst::getLLVMPrimitive() {
    return indirectBrInst;
}

Napi::Value IndirectBrInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = indirectBrInst->getType();
    return Type::New(env, type);
}

void IndirectBrInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        indirectBrInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IndirectBrInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        InvokeInst Class
//===----------------------------------------------------------------------===//

void InvokeInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "InvokeInst", {
            InstanceMethod("getType", &InvokeInst::getType),
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

Napi::Value InvokeInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = invokeInst->getType();
    return Type::New(env, type);
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
//                        CallBrInst Class
//===----------------------------------------------------------------------===//

void CallBrInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CallBrInst", {
            InstanceMethod("getType", &CallBrInst::getType),
            InstanceMethod("setDebugLoc", &CallBrInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CallBrInst", func);
}

Napi::Object CallBrInst::New(Napi::Env env, llvm::CallBrInst *callBrInst) {
    return constructor.New({Napi::External<llvm::CallBrInst>::New(env, callBrInst)});
}

bool CallBrInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CallBrInst *CallBrInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CallBrInst::CallBrInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CallBrInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CallBrInst>>();
    callBrInst = external.Data();
}

llvm::CallBrInst *CallBrInst::getLLVMPrimitive() {
    return callBrInst;
}

Napi::Value CallBrInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = callBrInst->getType();
    return Type::New(env, type);
}

void CallBrInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        callBrInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CallBrInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        ResumeInst Class
//===----------------------------------------------------------------------===//

void ResumeInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ResumeInst", {
            InstanceMethod("getType", &ResumeInst::getType),
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

Napi::Value ResumeInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = resumeInst->getType();
    return Type::New(env, type);
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
//                        CatchSwitchInst Class
//===----------------------------------------------------------------------===//

void CatchSwitchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CatchSwitchInst", {
            InstanceMethod("getType", &CatchSwitchInst::getType),
            InstanceMethod("setDebugLoc", &CatchSwitchInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CatchSwitchInst", func);
}

Napi::Object CatchSwitchInst::New(Napi::Env env, llvm::CatchSwitchInst *catchSwitchInst) {
    return constructor.New({Napi::External<llvm::CatchSwitchInst>::New(env, catchSwitchInst)});
}

bool CatchSwitchInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CatchSwitchInst *CatchSwitchInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CatchSwitchInst::CatchSwitchInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CatchSwitchInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CatchSwitchInst>>();
    catchSwitchInst = external.Data();
}

llvm::CatchSwitchInst *CatchSwitchInst::getLLVMPrimitive() {
    return catchSwitchInst;
}

Napi::Value CatchSwitchInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = catchSwitchInst->getType();
    return Type::New(env, type);
}

void CatchSwitchInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        catchSwitchInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CatchSwitchInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        CleanupPadInst Class
//===----------------------------------------------------------------------===//

void CleanupPadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CleanupPadInst", {
            InstanceMethod("getType", &CleanupPadInst::getType),
            InstanceMethod("setDebugLoc", &CleanupPadInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CleanupPadInst", func);
}

Napi::Object CleanupPadInst::New(Napi::Env env, llvm::CleanupPadInst *cleanupPadInst) {
    return constructor.New({Napi::External<llvm::CleanupPadInst>::New(env, cleanupPadInst)});
}

bool CleanupPadInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CleanupPadInst *CleanupPadInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CleanupPadInst::CleanupPadInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CleanupPadInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CleanupPadInst>>();
    cleanupPadInst = external.Data();
}

llvm::CleanupPadInst *CleanupPadInst::getLLVMPrimitive() {
    return cleanupPadInst;
}

Napi::Value CleanupPadInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = cleanupPadInst->getType();
    return Type::New(env, type);
}

void CleanupPadInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        cleanupPadInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CleanupPadInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        CatchPadInst Class
//===----------------------------------------------------------------------===//

void CatchPadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CatchPadInst", {
            InstanceMethod("getType", &CatchPadInst::getType),
            InstanceMethod("setDebugLoc", &CatchPadInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CatchPadInst", func);
}

Napi::Object CatchPadInst::New(Napi::Env env, llvm::CatchPadInst *catchPadInst) {
    return constructor.New({Napi::External<llvm::CatchPadInst>::New(env, catchPadInst)});
}

bool CatchPadInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CatchPadInst *CatchPadInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CatchPadInst::CatchPadInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CatchPadInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CatchPadInst>>();
    catchPadInst = external.Data();
}

llvm::CatchPadInst *CatchPadInst::getLLVMPrimitive() {
    return catchPadInst;
}

Napi::Value CatchPadInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = catchPadInst->getType();
    return Type::New(env, type);
}

void CatchPadInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        catchPadInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CatchPadInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        CatchReturnInst Class
//===----------------------------------------------------------------------===//

void CatchReturnInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CatchReturnInst", {
            InstanceMethod("getType", &CatchReturnInst::getType),
            InstanceMethod("setDebugLoc", &CatchReturnInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CatchReturnInst", func);
}

Napi::Object CatchReturnInst::New(Napi::Env env, llvm::CatchReturnInst *catchReturnInst) {
    return constructor.New({Napi::External<llvm::CatchReturnInst>::New(env, catchReturnInst)});
}

bool CatchReturnInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CatchReturnInst *CatchReturnInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CatchReturnInst::CatchReturnInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CatchReturnInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CatchReturnInst>>();
    catchReturnInst = external.Data();
}

llvm::CatchReturnInst *CatchReturnInst::getLLVMPrimitive() {
    return catchReturnInst;
}

Napi::Value CatchReturnInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = catchReturnInst->getType();
    return Type::New(env, type);
}

void CatchReturnInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        catchReturnInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CatchReturnInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        CleanupReturnInst Class
//===----------------------------------------------------------------------===//

void CleanupReturnInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CleanupReturnInst", {
            InstanceMethod("getType", &CleanupReturnInst::getType),
            InstanceMethod("setDebugLoc", &CleanupReturnInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CleanupReturnInst", func);
}

Napi::Object CleanupReturnInst::New(Napi::Env env, llvm::CleanupReturnInst *cleanupReturnInst) {
    return constructor.New({Napi::External<llvm::CleanupReturnInst>::New(env, cleanupReturnInst)});
}

bool CleanupReturnInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CleanupReturnInst *CleanupReturnInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CleanupReturnInst::CleanupReturnInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CleanupReturnInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CleanupReturnInst>>();
    cleanupReturnInst = external.Data();
}

llvm::CleanupReturnInst *CleanupReturnInst::getLLVMPrimitive() {
    return cleanupReturnInst;
}

Napi::Value CleanupReturnInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = cleanupReturnInst->getType();
    return Type::New(env, type);
}

void CleanupReturnInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        cleanupReturnInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::CleanupReturnInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        UnreachableInst Class
//===----------------------------------------------------------------------===//

void UnreachableInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "UnreachableInst", {
            InstanceMethod("getType", &UnreachableInst::getType),
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

Napi::Value UnreachableInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = unreachableInst->getType();
    return Type::New(env, type);
}

void UnreachableInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        unreachableInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::UnreachableInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        TruncInst Class
//===----------------------------------------------------------------------===//

void TruncInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "TruncInst", {
            InstanceMethod("getType", &TruncInst::getType),
            InstanceMethod("setDebugLoc", &TruncInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("TruncInst", func);
}

Napi::Object TruncInst::New(Napi::Env env, llvm::TruncInst *truncInst) {
    return constructor.New({Napi::External<llvm::TruncInst>::New(env, truncInst)});
}

bool TruncInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::TruncInst *TruncInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

TruncInst::TruncInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::TruncInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::TruncInst>>();
    truncInst = external.Data();
}

llvm::TruncInst *TruncInst::getLLVMPrimitive() {
    return truncInst;
}

Napi::Value TruncInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = truncInst->getType();
    return Type::New(env, type);
}

void TruncInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        truncInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::TruncInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        ZExtInst Class
//===----------------------------------------------------------------------===//

void ZExtInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ZExtInst", {
            InstanceMethod("getType", &ZExtInst::getType),
            InstanceMethod("setDebugLoc", &ZExtInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ZExtInst", func);
}

Napi::Object ZExtInst::New(Napi::Env env, llvm::ZExtInst *zExtInst) {
    return constructor.New({Napi::External<llvm::ZExtInst>::New(env, zExtInst)});
}

bool ZExtInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ZExtInst *ZExtInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ZExtInst::ZExtInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ZExtInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ZExtInst>>();
    zExtInst = external.Data();
}

llvm::ZExtInst *ZExtInst::getLLVMPrimitive() {
    return zExtInst;
}

Napi::Value ZExtInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = zExtInst->getType();
    return Type::New(env, type);
}

void ZExtInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        zExtInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::ZExtInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        SExtInst Class
//===----------------------------------------------------------------------===//

void SExtInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SExtInst", {
            InstanceMethod("getType", &SExtInst::getType),
            InstanceMethod("setDebugLoc", &SExtInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("SExtInst", func);
}

Napi::Object SExtInst::New(Napi::Env env, llvm::SExtInst *sExtInst) {
    return constructor.New({Napi::External<llvm::SExtInst>::New(env, sExtInst)});
}

bool SExtInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SExtInst *SExtInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SExtInst::SExtInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SExtInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::SExtInst>>();
    sExtInst = external.Data();
}

llvm::SExtInst *SExtInst::getLLVMPrimitive() {
    return sExtInst;
}

Napi::Value SExtInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = sExtInst->getType();
    return Type::New(env, type);
}

void SExtInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        sExtInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SExtInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FPTruncInst Class
//===----------------------------------------------------------------------===//

void FPTruncInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FPTruncInst", {
            InstanceMethod("getType", &FPTruncInst::getType),
            InstanceMethod("setDebugLoc", &FPTruncInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FPTruncInst", func);
}

Napi::Object FPTruncInst::New(Napi::Env env, llvm::FPTruncInst *fpTruncInst) {
    return constructor.New({Napi::External<llvm::FPTruncInst>::New(env, fpTruncInst)});
}

bool FPTruncInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FPTruncInst *FPTruncInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FPTruncInst::FPTruncInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FPTruncInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FPTruncInst>>();
    fpTruncInst = external.Data();
}

llvm::FPTruncInst *FPTruncInst::getLLVMPrimitive() {
    return fpTruncInst;
}

Napi::Value FPTruncInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fpTruncInst->getType();
    return Type::New(env, type);
}

void FPTruncInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fpTruncInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FPTruncInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FPExtInst Class
//===----------------------------------------------------------------------===//

void FPExtInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FPExtInst", {
            InstanceMethod("getType", &FPExtInst::getType),
            InstanceMethod("setDebugLoc", &FPExtInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FPExtInst", func);
}

Napi::Object FPExtInst::New(Napi::Env env, llvm::FPExtInst *fpExtInst) {
    return constructor.New({Napi::External<llvm::FPExtInst>::New(env, fpExtInst)});
}

bool FPExtInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FPExtInst *FPExtInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FPExtInst::FPExtInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FPExtInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FPExtInst>>();
    fpExtInst = external.Data();
}

llvm::FPExtInst *FPExtInst::getLLVMPrimitive() {
    return fpExtInst;
}

Napi::Value FPExtInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fpExtInst->getType();
    return Type::New(env, type);
}

void FPExtInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fpExtInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FPExtInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        UIToFPInst Class
//===----------------------------------------------------------------------===//

void UIToFPInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "UIToFPInst", {
            InstanceMethod("getType", &UIToFPInst::getType),
            InstanceMethod("setDebugLoc", &UIToFPInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("UIToFPInst", func);
}

Napi::Object UIToFPInst::New(Napi::Env env, llvm::UIToFPInst *uiToFPInst) {
    return constructor.New({Napi::External<llvm::UIToFPInst>::New(env, uiToFPInst)});
}

bool UIToFPInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::UIToFPInst *UIToFPInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

UIToFPInst::UIToFPInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::UIToFPInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::UIToFPInst>>();
    uiToFPInst = external.Data();
}

llvm::UIToFPInst *UIToFPInst::getLLVMPrimitive() {
    return uiToFPInst;
}

Napi::Value UIToFPInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = uiToFPInst->getType();
    return Type::New(env, type);
}

void UIToFPInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        uiToFPInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::UIToFPInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        SIToFPInst Class
//===----------------------------------------------------------------------===//

void SIToFPInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SIToFPInst", {
            InstanceMethod("getType", &SIToFPInst::getType),
            InstanceMethod("setDebugLoc", &SIToFPInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("SIToFPInst", func);
}

Napi::Object SIToFPInst::New(Napi::Env env, llvm::SIToFPInst *siToFPInst) {
    return constructor.New({Napi::External<llvm::SIToFPInst>::New(env, siToFPInst)});
}

bool SIToFPInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SIToFPInst *SIToFPInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SIToFPInst::SIToFPInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SIToFPInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::SIToFPInst>>();
    siToFPInst = external.Data();
}

llvm::SIToFPInst *SIToFPInst::getLLVMPrimitive() {
    return siToFPInst;
}

Napi::Value SIToFPInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = siToFPInst->getType();
    return Type::New(env, type);
}

void SIToFPInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        siToFPInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::SIToFPInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FPToUIInst Class
//===----------------------------------------------------------------------===//

void FPToUIInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FPToUIInst", {
            InstanceMethod("getType", &FPToUIInst::getType),
            InstanceMethod("setDebugLoc", &FPToUIInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FPToUIInst", func);
}

Napi::Object FPToUIInst::New(Napi::Env env, llvm::FPToUIInst *fpToUIInst) {
    return constructor.New({Napi::External<llvm::FPToUIInst>::New(env, fpToUIInst)});
}

bool FPToUIInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FPToUIInst *FPToUIInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FPToUIInst::FPToUIInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FPToUIInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FPToUIInst>>();
    fpToUIInst = external.Data();
}

llvm::FPToUIInst *FPToUIInst::getLLVMPrimitive() {
    return fpToUIInst;
}

Napi::Value FPToUIInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fpToUIInst->getType();
    return Type::New(env, type);
}

void FPToUIInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fpToUIInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FPToUIInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FPToSIInst Class
//===----------------------------------------------------------------------===//

void FPToSIInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FPToSIInst", {
            InstanceMethod("getType", &FPToSIInst::getType),
            InstanceMethod("setDebugLoc", &FPToSIInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FPToSIInst", func);
}

Napi::Object FPToSIInst::New(Napi::Env env, llvm::FPToSIInst *fpToSIInst) {
    return constructor.New({Napi::External<llvm::FPToSIInst>::New(env, fpToSIInst)});
}

bool FPToSIInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FPToSIInst *FPToSIInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FPToSIInst::FPToSIInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FPToSIInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FPToSIInst>>();
    fpToSIInst = external.Data();
}

llvm::FPToSIInst *FPToSIInst::getLLVMPrimitive() {
    return fpToSIInst;
}

Napi::Value FPToSIInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = fpToSIInst->getType();
    return Type::New(env, type);
}

void FPToSIInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        fpToSIInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FPToSIInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        IntToPtrInst Class
//===----------------------------------------------------------------------===//

void IntToPtrInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IntToPtrInst", {
            InstanceMethod("getType", &IntToPtrInst::getType),
            InstanceMethod("setDebugLoc", &IntToPtrInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("IntToPtrInst", func);
}

Napi::Object IntToPtrInst::New(Napi::Env env, llvm::IntToPtrInst *intToPtrInst) {
    return constructor.New({Napi::External<llvm::IntToPtrInst>::New(env, intToPtrInst)});
}

bool IntToPtrInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::IntToPtrInst *IntToPtrInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IntToPtrInst::IntToPtrInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntToPtrInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::IntToPtrInst>>();
    intToPtrInst = external.Data();
}

llvm::IntToPtrInst *IntToPtrInst::getLLVMPrimitive() {
    return intToPtrInst;
}

Napi::Value IntToPtrInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = intToPtrInst->getType();
    return Type::New(env, type);
}

void IntToPtrInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        intToPtrInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IntToPtrInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        PtrToIntInst Class
//===----------------------------------------------------------------------===//

void PtrToIntInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PtrToIntInst", {
            InstanceMethod("getType", &PtrToIntInst::getType),
            InstanceMethod("setDebugLoc", &PtrToIntInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("PtrToIntInst", func);
}

Napi::Object PtrToIntInst::New(Napi::Env env, llvm::PtrToIntInst *ptrToIntInst) {
    return constructor.New({Napi::External<llvm::PtrToIntInst>::New(env, ptrToIntInst)});
}

bool PtrToIntInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::PtrToIntInst *PtrToIntInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

PtrToIntInst::PtrToIntInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PtrToIntInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::PtrToIntInst>>();
    ptrToIntInst = external.Data();
}

llvm::PtrToIntInst *PtrToIntInst::getLLVMPrimitive() {
    return ptrToIntInst;
}

Napi::Value PtrToIntInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = ptrToIntInst->getType();
    return Type::New(env, type);
}

void PtrToIntInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        ptrToIntInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::PtrToIntInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        BitCastInst Class
//===----------------------------------------------------------------------===//

void BitCastInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "BitCastInst", {
            InstanceMethod("getType", &BitCastInst::getType),
            InstanceMethod("setDebugLoc", &BitCastInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("BitCastInst", func);
}

Napi::Object BitCastInst::New(Napi::Env env, llvm::BitCastInst *bitCastInst) {
    return constructor.New({Napi::External<llvm::BitCastInst>::New(env, bitCastInst)});
}

bool BitCastInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::BitCastInst *BitCastInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

BitCastInst::BitCastInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::BitCastInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::BitCastInst>>();
    bitCastInst = external.Data();
}

llvm::BitCastInst *BitCastInst::getLLVMPrimitive() {
    return bitCastInst;
}

Napi::Value BitCastInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = bitCastInst->getType();
    return Type::New(env, type);
}

void BitCastInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        bitCastInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::BitCastInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        AddrSpaceCastInst Class
//===----------------------------------------------------------------------===//

void AddrSpaceCastInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "AddrSpaceCastInst", {
            InstanceMethod("getType", &AddrSpaceCastInst::getType),
            InstanceMethod("setDebugLoc", &AddrSpaceCastInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("AddrSpaceCastInst", func);
}

Napi::Object AddrSpaceCastInst::New(Napi::Env env, llvm::AddrSpaceCastInst *addrSpaceCastInst) {
    return constructor.New({Napi::External<llvm::AddrSpaceCastInst>::New(env, addrSpaceCastInst)});
}

bool AddrSpaceCastInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::AddrSpaceCastInst *AddrSpaceCastInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

AddrSpaceCastInst::AddrSpaceCastInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::AddrSpaceCastInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::AddrSpaceCastInst>>();
    addrSpaceCastInst = external.Data();
}

llvm::AddrSpaceCastInst *AddrSpaceCastInst::getLLVMPrimitive() {
    return addrSpaceCastInst;
}

Napi::Value AddrSpaceCastInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = addrSpaceCastInst->getType();
    return Type::New(env, type);
}

void AddrSpaceCastInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        addrSpaceCastInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::AddrSpaceCastInst::setDebugLoc);
}

//===----------------------------------------------------------------------===//
//                        FreezeInst Class
//===----------------------------------------------------------------------===//

void FreezeInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FreezeInst", {
            InstanceMethod("getType", &FreezeInst::getType),
            InstanceMethod("setDebugLoc", &FreezeInst::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("FreezeInst", func);
}

Napi::Object FreezeInst::New(Napi::Env env, llvm::FreezeInst *freezeInst) {
    return constructor.New({Napi::External<llvm::FreezeInst>::New(env, freezeInst)});
}

bool FreezeInst::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FreezeInst *FreezeInst::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FreezeInst::FreezeInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FreezeInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FreezeInst>>();
    freezeInst = external.Data();
}

llvm::FreezeInst *FreezeInst::getLLVMPrimitive() {
    return freezeInst;
}

Napi::Value FreezeInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = freezeInst->getType();
    return Type::New(env, type);
}

void FreezeInst::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        freezeInst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::FreezeInst::setDebugLoc);
}
