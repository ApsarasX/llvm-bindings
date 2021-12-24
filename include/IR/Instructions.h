#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class AllocaInst : public Napi::ObjectWrap<AllocaInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::AllocaInst *allocaInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::AllocaInst *Extract(const Napi::Value &value);

    explicit AllocaInst(const Napi::CallbackInfo &info);

    llvm::AllocaInst *getLLVMPrimitive();

private:
    llvm::AllocaInst *allocaInst = nullptr;

    Napi::Value getAllocatedType(const Napi::CallbackInfo &info);

    Napi::Value getArraySize(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class LoadInst : public Napi::ObjectWrap<LoadInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::LoadInst *loadInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::LoadInst *Extract(const Napi::Value &value);

    explicit LoadInst(const Napi::CallbackInfo &info);

    llvm::LoadInst *getLLVMPrimitive();

private:
    llvm::LoadInst *loadInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class StoreInst : public Napi::ObjectWrap<StoreInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::StoreInst *storeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::StoreInst *Extract(const Napi::Value &value);

    explicit StoreInst(const Napi::CallbackInfo &info);

    llvm::StoreInst *getLLVMPrimitive();

private:
    llvm::StoreInst *storeInst = nullptr;

    Napi::Value getValueOperand(const Napi::CallbackInfo &info);

    Napi::Value getPointerOperand(const Napi::CallbackInfo &info);

    Napi::Value getPointerOperandType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class GetElementPtrInst : public Napi::ObjectWrap<GetElementPtrInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::GetElementPtrInst *gepInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::GetElementPtrInst *Extract(const Napi::Value &value);

    explicit GetElementPtrInst(const Napi::CallbackInfo &info);

    llvm::GetElementPtrInst *getLLVMPrimitive();

private:
    llvm::GetElementPtrInst *gepInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CallInst : public Napi::ObjectWrap<CallInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CallInst *callInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CallInst *Extract(const Napi::Value &value);

    explicit CallInst(const Napi::CallbackInfo &info);

    llvm::CallInst *getLLVMPrimitive();

private:
    llvm::CallInst *callInst = nullptr;

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class PHINode : public Napi::ObjectWrap<PHINode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::PHINode *phiNode);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::PHINode *Extract(const Napi::Value &value);

    explicit PHINode(const Napi::CallbackInfo &info);

    llvm::PHINode *getLLVMPrimitive();

private:
    llvm::PHINode *phiNode = nullptr;

    void addIncoming(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class LandingPadInst : public Napi::ObjectWrap<LandingPadInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::LandingPadInst *lpInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::LandingPadInst *Extract(const Napi::Value &value);

    explicit LandingPadInst(const Napi::CallbackInfo &info);

    llvm::LandingPadInst *getLLVMPrimitive();

private:
    llvm::LandingPadInst *lpInst = nullptr;

    void setCleanup(const Napi::CallbackInfo &info);

    void addClause(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ReturnInst : public Napi::ObjectWrap<ReturnInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ReturnInst *returnInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ReturnInst *Extract(const Napi::Value &value);

    explicit ReturnInst(const Napi::CallbackInfo &info);

    llvm::ReturnInst *getLLVMPrimitive();

private:
    llvm::ReturnInst *returnInst = nullptr;

    Napi::Value getReturnValue(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class BranchInst : public Napi::ObjectWrap<BranchInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::BranchInst *branchInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::BranchInst *Extract(const Napi::Value &value);

    explicit BranchInst(const Napi::CallbackInfo &info);

    llvm::BranchInst *getLLVMPrimitive();

private:
    llvm::BranchInst *branchInst = nullptr;

    Napi::Value isUnconditional(const Napi::CallbackInfo &info);

    Napi::Value isConditional(const Napi::CallbackInfo &info);

    Napi::Value getCondition(const Napi::CallbackInfo &info);

    Napi::Value getNumSuccessors(const Napi::CallbackInfo &info);

    Napi::Value getSuccessor(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class SwitchInst : public Napi::ObjectWrap<SwitchInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::SwitchInst *switchInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SwitchInst *Extract(const Napi::Value &value);

    explicit SwitchInst(const Napi::CallbackInfo &info);

    llvm::SwitchInst *getLLVMPrimitive();

private:
    llvm::SwitchInst *switchInst = nullptr;

    void addCase(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class InvokeInst : public Napi::ObjectWrap<InvokeInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::InvokeInst *callInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::InvokeInst *Extract(const Napi::Value &value);

    explicit InvokeInst(const Napi::CallbackInfo &info);

    llvm::InvokeInst *getLLVMPrimitive();

private:
    llvm::InvokeInst *invokeInst = nullptr;

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ResumeInst : public Napi::ObjectWrap<ResumeInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ResumeInst *resumeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ResumeInst *Extract(const Napi::Value &value);

    explicit ResumeInst(const Napi::CallbackInfo &info);

    llvm::ResumeInst *getLLVMPrimitive();

private:
    llvm::ResumeInst *resumeInst = nullptr;

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class UnreachableInst : public Napi::ObjectWrap<UnreachableInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::UnreachableInst *unreachableInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::UnreachableInst *Extract(const Napi::Value &value);

    explicit UnreachableInst(const Napi::CallbackInfo &info);

    llvm::UnreachableInst *getLLVMPrimitive();

private:
    llvm::UnreachableInst *unreachableInst = nullptr;

    void setDebugLoc(const Napi::CallbackInfo &info);
};
