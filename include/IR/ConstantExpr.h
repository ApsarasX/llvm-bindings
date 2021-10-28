#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantExpr : public Napi::ObjectWrap<ConstantExpr> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantExpr *constantExpr);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantExpr *Extract(const Napi::Value &value);

    explicit ConstantExpr(const Napi::CallbackInfo &info);

    llvm::ConstantExpr *getLLVMPrimitive();

private:
    llvm::ConstantExpr *constantExpr = nullptr;

    static Napi::Value getBitCast(const Napi::CallbackInfo &info);
};
