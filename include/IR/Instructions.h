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

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FenceInst : public Napi::ObjectWrap<FenceInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FenceInst *fenceInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FenceInst *Extract(const Napi::Value &value);

    explicit FenceInst(const Napi::CallbackInfo &info);

    llvm::FenceInst *getLLVMPrimitive();

private:
    llvm::FenceInst *fenceInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class AtomicCmpXchgInst : public Napi::ObjectWrap<AtomicCmpXchgInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::AtomicCmpXchgInst *atomicCmpXchgInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::AtomicCmpXchgInst *Extract(const Napi::Value &value);

    explicit AtomicCmpXchgInst(const Napi::CallbackInfo &info);

    llvm::AtomicCmpXchgInst *getLLVMPrimitive();

private:
    llvm::AtomicCmpXchgInst *atomicCmpXchgInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class AtomicRMWInst : public Napi::ObjectWrap<AtomicRMWInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::AtomicRMWInst *atomicRMWInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::AtomicRMWInst *Extract(const Napi::Value &value);

    explicit AtomicRMWInst(const Napi::CallbackInfo &info);

    llvm::AtomicRMWInst *getLLVMPrimitive();

private:
    llvm::AtomicRMWInst *atomicRMWInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

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

class ICmpInst : public Napi::ObjectWrap<ICmpInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ICmpInst *icmpInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ICmpInst *Extract(const Napi::Value &value);

    explicit ICmpInst(const Napi::CallbackInfo &info);

    llvm::ICmpInst *getLLVMPrimitive();

private:
    llvm::ICmpInst *icmpInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FCmpInst : public Napi::ObjectWrap<FCmpInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FCmpInst *fcmpInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FCmpInst *Extract(const Napi::Value &value);

    explicit FCmpInst(const Napi::CallbackInfo &info);

    llvm::FCmpInst *getLLVMPrimitive();

private:
    llvm::FCmpInst *fcmpInst = nullptr;

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

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class SelectInst : public Napi::ObjectWrap<SelectInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::SelectInst *selectInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SelectInst *Extract(const Napi::Value &value);

    explicit SelectInst(const Napi::CallbackInfo &info);

    llvm::SelectInst *getLLVMPrimitive();

private:
    llvm::SelectInst *selectInst = nullptr;

    Napi::Value getCondition(const Napi::CallbackInfo &info);

    Napi::Value getTrueValue(const Napi::CallbackInfo &info);

    Napi::Value getFalseValue(const Napi::CallbackInfo &info);

    void setCondition(const Napi::CallbackInfo &info);

    void setTrueValue(const Napi::CallbackInfo &info);

    void setFalseValue(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class VAArgInst : public Napi::ObjectWrap<VAArgInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::VAArgInst *vaArgInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::VAArgInst *Extract(const Napi::Value &value);

    explicit VAArgInst(const Napi::CallbackInfo &info);

    llvm::VAArgInst *getLLVMPrimitive();

private:
    llvm::VAArgInst *vaArgInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ExtractElementInst : public Napi::ObjectWrap<ExtractElementInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ExtractElementInst *extractElementInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ExtractElementInst *Extract(const Napi::Value &value);

    explicit ExtractElementInst(const Napi::CallbackInfo &info);

    llvm::ExtractElementInst *getLLVMPrimitive();

private:
    llvm::ExtractElementInst *extractElementInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class InsertElementInst : public Napi::ObjectWrap<InsertElementInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::InsertElementInst *insertElementInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::InsertElementInst *Extract(const Napi::Value &value);

    explicit InsertElementInst(const Napi::CallbackInfo &info);

    llvm::InsertElementInst *getLLVMPrimitive();

private:
    llvm::InsertElementInst *insertElementInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ShuffleVectorInst : public Napi::ObjectWrap<ShuffleVectorInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ShuffleVectorInst *shuffleVectorInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ShuffleVectorInst *Extract(const Napi::Value &value);

    explicit ShuffleVectorInst(const Napi::CallbackInfo &info);

    llvm::ShuffleVectorInst *getLLVMPrimitive();

private:
    llvm::ShuffleVectorInst *shuffleVectorInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ExtractValueInst : public Napi::ObjectWrap<ExtractValueInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ExtractValueInst *extractValueInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ExtractValueInst *Extract(const Napi::Value &value);

    explicit ExtractValueInst(const Napi::CallbackInfo &info);

    llvm::ExtractValueInst *getLLVMPrimitive();

private:
    llvm::ExtractValueInst *extractValueInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class InsertValueInst : public Napi::ObjectWrap<InsertValueInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::InsertValueInst *insertValueInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::InsertValueInst *Extract(const Napi::Value &value);

    explicit InsertValueInst(const Napi::CallbackInfo &info);

    llvm::InsertValueInst *getLLVMPrimitive();

private:
    llvm::InsertValueInst *insertValueInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class IndirectBrInst : public Napi::ObjectWrap<IndirectBrInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::IndirectBrInst *indirectBrInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::IndirectBrInst *Extract(const Napi::Value &value);

    explicit IndirectBrInst(const Napi::CallbackInfo &info);

    llvm::IndirectBrInst *getLLVMPrimitive();

private:
    llvm::IndirectBrInst *indirectBrInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class InvokeInst : public Napi::ObjectWrap<InvokeInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::InvokeInst *invokeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::InvokeInst *Extract(const Napi::Value &value);

    explicit InvokeInst(const Napi::CallbackInfo &info);

    llvm::InvokeInst *getLLVMPrimitive();

private:
    llvm::InvokeInst *invokeInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CallBrInst : public Napi::ObjectWrap<CallBrInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CallBrInst *callBrInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CallBrInst *Extract(const Napi::Value &value);

    explicit CallBrInst(const Napi::CallbackInfo &info);

    llvm::CallBrInst *getLLVMPrimitive();

private:
    llvm::CallBrInst *callBrInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CatchSwitchInst : public Napi::ObjectWrap<CatchSwitchInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CatchSwitchInst *catchSwitchInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CatchSwitchInst *Extract(const Napi::Value &value);

    explicit CatchSwitchInst(const Napi::CallbackInfo &info);

    llvm::CatchSwitchInst *getLLVMPrimitive();

private:
    llvm::CatchSwitchInst *catchSwitchInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CleanupPadInst : public Napi::ObjectWrap<CleanupPadInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CleanupPadInst *CleanupPadInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CleanupPadInst *Extract(const Napi::Value &value);

    explicit CleanupPadInst(const Napi::CallbackInfo &info);

    llvm::CleanupPadInst *getLLVMPrimitive();

private:
    llvm::CleanupPadInst *cleanupPadInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CatchPadInst : public Napi::ObjectWrap<CatchPadInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CatchPadInst *catchPadInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CatchPadInst *Extract(const Napi::Value &value);

    explicit CatchPadInst(const Napi::CallbackInfo &info);

    llvm::CatchPadInst *getLLVMPrimitive();

private:
    llvm::CatchPadInst *catchPadInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CatchReturnInst : public Napi::ObjectWrap<CatchReturnInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CatchReturnInst *catchReturnInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CatchReturnInst *Extract(const Napi::Value &value);

    explicit CatchReturnInst(const Napi::CallbackInfo &info);

    llvm::CatchReturnInst *getLLVMPrimitive();

private:
    llvm::CatchReturnInst *catchReturnInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class CleanupReturnInst : public Napi::ObjectWrap<CleanupReturnInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CleanupReturnInst *cleanupReturnInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CleanupReturnInst *Extract(const Napi::Value &value);

    explicit CleanupReturnInst(const Napi::CallbackInfo &info);

    llvm::CleanupReturnInst *getLLVMPrimitive();

private:
    llvm::CleanupReturnInst *cleanupReturnInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

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

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class TruncInst : public Napi::ObjectWrap<TruncInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::TruncInst *truncInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::TruncInst *Extract(const Napi::Value &value);

    explicit TruncInst(const Napi::CallbackInfo &info);

    llvm::TruncInst *getLLVMPrimitive();

private:
    llvm::TruncInst *truncInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class ZExtInst : public Napi::ObjectWrap<ZExtInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ZExtInst *zExtInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ZExtInst *Extract(const Napi::Value &value);

    explicit ZExtInst(const Napi::CallbackInfo &info);

    llvm::ZExtInst *getLLVMPrimitive();

private:
    llvm::ZExtInst *zExtInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class SExtInst : public Napi::ObjectWrap<SExtInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::SExtInst *sExtInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SExtInst *Extract(const Napi::Value &value);

    explicit SExtInst(const Napi::CallbackInfo &info);

    llvm::SExtInst *getLLVMPrimitive();

private:
    llvm::SExtInst *sExtInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FPTruncInst : public Napi::ObjectWrap<FPTruncInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FPTruncInst *fpTruncInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FPTruncInst *Extract(const Napi::Value &value);

    explicit FPTruncInst(const Napi::CallbackInfo &info);

    llvm::FPTruncInst *getLLVMPrimitive();

private:
    llvm::FPTruncInst *fpTruncInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FPExtInst : public Napi::ObjectWrap<FPExtInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FPExtInst *fpExtInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FPExtInst *Extract(const Napi::Value &value);

    explicit FPExtInst(const Napi::CallbackInfo &info);

    llvm::FPExtInst *getLLVMPrimitive();

private:
    llvm::FPExtInst *fpExtInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class UIToFPInst : public Napi::ObjectWrap<UIToFPInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::UIToFPInst *uiToFPInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::UIToFPInst *Extract(const Napi::Value &value);

    explicit UIToFPInst(const Napi::CallbackInfo &info);

    llvm::UIToFPInst *getLLVMPrimitive();

private:
    llvm::UIToFPInst *uiToFPInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class SIToFPInst : public Napi::ObjectWrap<SIToFPInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::SIToFPInst *siToFPInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SIToFPInst *Extract(const Napi::Value &value);

    explicit SIToFPInst(const Napi::CallbackInfo &info);

    llvm::SIToFPInst *getLLVMPrimitive();

private:
    llvm::SIToFPInst *siToFPInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FPToUIInst : public Napi::ObjectWrap<FPToUIInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FPToUIInst *fpToUIInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FPToUIInst *Extract(const Napi::Value &value);

    explicit FPToUIInst(const Napi::CallbackInfo &info);

    llvm::FPToUIInst *getLLVMPrimitive();

private:
    llvm::FPToUIInst *fpToUIInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FPToSIInst : public Napi::ObjectWrap<FPToSIInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FPToSIInst *fpToSIInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FPToSIInst *Extract(const Napi::Value &value);

    explicit FPToSIInst(const Napi::CallbackInfo &info);

    llvm::FPToSIInst *getLLVMPrimitive();

private:
    llvm::FPToSIInst *fpToSIInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class IntToPtrInst : public Napi::ObjectWrap<IntToPtrInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::IntToPtrInst *intToPtrInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::IntToPtrInst *Extract(const Napi::Value &value);

    explicit IntToPtrInst(const Napi::CallbackInfo &info);

    llvm::IntToPtrInst *getLLVMPrimitive();

private:
    llvm::IntToPtrInst *intToPtrInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class PtrToIntInst : public Napi::ObjectWrap<PtrToIntInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::PtrToIntInst *ptrToIntInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::PtrToIntInst *Extract(const Napi::Value &value);

    explicit PtrToIntInst(const Napi::CallbackInfo &info);

    llvm::PtrToIntInst *getLLVMPrimitive();

private:
    llvm::PtrToIntInst *ptrToIntInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class BitCastInst : public Napi::ObjectWrap<BitCastInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::BitCastInst *bitCastInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::BitCastInst *Extract(const Napi::Value &value);

    explicit BitCastInst(const Napi::CallbackInfo &info);

    llvm::BitCastInst *getLLVMPrimitive();

private:
    llvm::BitCastInst *bitCastInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class AddrSpaceCastInst : public Napi::ObjectWrap<AddrSpaceCastInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::AddrSpaceCastInst *addrSpaceCastInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::AddrSpaceCastInst *Extract(const Napi::Value &value);

    explicit AddrSpaceCastInst(const Napi::CallbackInfo &info);

    llvm::AddrSpaceCastInst *getLLVMPrimitive();

private:
    llvm::AddrSpaceCastInst *addrSpaceCastInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};

class FreezeInst : public Napi::ObjectWrap<FreezeInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FreezeInst *freezeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FreezeInst *Extract(const Napi::Value &value);

    explicit FreezeInst(const Napi::CallbackInfo &info);

    llvm::FreezeInst *getLLVMPrimitive();

private:
    llvm::FreezeInst *freezeInst = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};
