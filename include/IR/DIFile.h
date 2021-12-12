#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIFile : public Napi::ObjectWrap<DIFile> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIFile *file);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIFile *Extract(const Napi::Value &value);

    explicit DIFile(const Napi::CallbackInfo &info);

    llvm::DIFile *getLLVMPrimitive();

private:
    llvm::DIFile *file = nullptr;
};