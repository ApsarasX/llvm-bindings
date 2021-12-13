#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIGlobalVariable : public Napi::ObjectWrap<DIGlobalVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIGlobalVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIGlobalVariable *Extract(const Napi::Value &value);

    explicit DIGlobalVariable(const Napi::CallbackInfo &info);

    llvm::DIGlobalVariable *getLLVMPrimitive();

private:
    llvm::DIGlobalVariable *variable = nullptr;
};