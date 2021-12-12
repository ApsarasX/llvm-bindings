#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DITypeRefArray : public Napi::ObjectWrap<DITypeRefArray> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DITypeRefArray *array);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DITypeRefArray *Extract(const Napi::Value &value);

    explicit DITypeRefArray(const Napi::CallbackInfo &info);

    llvm::DITypeRefArray *getLLVMPrimitive();

private:
    llvm::DITypeRefArray *array = nullptr;
};