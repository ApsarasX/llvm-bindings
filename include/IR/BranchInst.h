#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class BranchInst : public Napi::ObjectWrap<BranchInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::BranchInst *BranchInst);

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
};