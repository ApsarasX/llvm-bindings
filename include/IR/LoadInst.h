#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

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
};