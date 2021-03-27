#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class CallInst : public Napi::ObjectWrap<CallInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::CallInst *CallInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::CallInst *Extract(const Napi::Value &value);

    explicit CallInst(const Napi::CallbackInfo &info);

    llvm::CallInst *getLLVMPrimitive();

private:
    llvm::CallInst *callInst = nullptr;
};