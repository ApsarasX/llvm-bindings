#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

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