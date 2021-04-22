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
};