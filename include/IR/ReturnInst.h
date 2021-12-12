#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

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