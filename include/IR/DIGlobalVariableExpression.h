#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIGlobalVariableExpression : public Napi::ObjectWrap<DIGlobalVariableExpression> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIGlobalVariableExpression *expression);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIGlobalVariableExpression *Extract(const Napi::Value &value);

    explicit DIGlobalVariableExpression(const Napi::CallbackInfo &info);

    llvm::DIGlobalVariableExpression *getLLVMPrimitive();

private:
    llvm::DIGlobalVariableExpression *expression = nullptr;
};