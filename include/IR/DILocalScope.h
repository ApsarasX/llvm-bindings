#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DILocalScope : public Napi::ObjectWrap<DILocalScope> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocalScope *scope);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocalScope *Extract(const Napi::Value &value);

    explicit DILocalScope(const Napi::CallbackInfo &info);

    llvm::DILocalScope *getLLVMPrimitive();

private:
    llvm::DILocalScope *scope = nullptr;
};