#pragma once

#include <napi.h>
#include <llvm/IR/LLVMContext.h>

class LLVMContext : public Napi::ObjectWrap<LLVMContext> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::LLVMContext &Extract(const Napi::Value &value);

    explicit LLVMContext(const Napi::CallbackInfo &info);

    llvm::LLVMContext &getLLVMPrimitive();

private:
    llvm::LLVMContext *context = nullptr;
};
