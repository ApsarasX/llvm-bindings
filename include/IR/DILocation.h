#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DILocation : public Napi::ObjectWrap<DILocation> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocation *location);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocation *Extract(const Napi::Value &value);

    explicit DILocation(const Napi::CallbackInfo &info);

    llvm::DILocation *getLLVMPrimitive();

private:
    llvm::DILocation *location = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};