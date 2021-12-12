#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIScope : public Napi::ObjectWrap<DIScope> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIScope *scope);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIScope *Extract(const Napi::Value &value);

    explicit DIScope(const Napi::CallbackInfo &info);

    llvm::DIScope *getLLVMPrimitive();

private:
    llvm::DIScope *scope = nullptr;
};