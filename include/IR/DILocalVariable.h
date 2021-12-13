#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DILocalVariable : public Napi::ObjectWrap<DILocalVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocalVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocalVariable *Extract(const Napi::Value &value);

    explicit DILocalVariable(const Napi::CallbackInfo &info);

    llvm::DILocalVariable *getLLVMPrimitive();

private:
    llvm::DILocalVariable *variable = nullptr;
};