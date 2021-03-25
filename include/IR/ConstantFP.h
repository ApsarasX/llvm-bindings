#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantFP : public Napi::ObjectWrap<ConstantFP> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantFP *constantFP);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantFP *Extract(const Napi::Value &value);

    explicit ConstantFP(const Napi::CallbackInfo &info);

    llvm::ConstantFP *getLLVMPrimitive();

private:
    llvm::ConstantFP *constantFP = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};
