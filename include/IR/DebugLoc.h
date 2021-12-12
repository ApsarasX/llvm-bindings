#pragma once

#include <napi.h>
#include <llvm/IR/DebugLoc.h>

class DebugLoc : public Napi::ObjectWrap<DebugLoc> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DebugLoc *location);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DebugLoc *Extract(const Napi::Value &value);

    explicit DebugLoc(const Napi::CallbackInfo &info);

    llvm::DebugLoc *getLLVMPrimitive();

private:
    llvm::DebugLoc *location = nullptr;
};