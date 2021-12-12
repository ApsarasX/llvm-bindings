#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIType : public Napi::ObjectWrap<DIType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIType *Extract(const Napi::Value &value);

    explicit DIType(const Napi::CallbackInfo &info);

    llvm::DIType *getLLVMPrimitive();

private:
    llvm::DIType *type = nullptr;
};