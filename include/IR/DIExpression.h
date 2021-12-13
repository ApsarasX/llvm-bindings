#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIExpression : public Napi::ObjectWrap<DIExpression> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIExpression *expression);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIExpression *Extract(const Napi::Value &value);

    explicit DIExpression(const Napi::CallbackInfo &info);

    llvm::DIExpression *getLLVMPrimitive();

private:
    llvm::DIExpression *expression = nullptr;
};