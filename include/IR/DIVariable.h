#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIVariable : public Napi::ObjectWrap<DIVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIVariable *Extract(const Napi::Value &value);

    explicit DIVariable(const Napi::CallbackInfo &info);

    llvm::DIVariable *getLLVMPrimitive();

private:
    llvm::DIVariable *variable = nullptr;
};