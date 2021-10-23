#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

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
};
