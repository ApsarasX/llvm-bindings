#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class UndefValue : public Napi::ObjectWrap<UndefValue> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::UndefValue *undefValue);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::UndefValue *Extract(const Napi::Value &value);

    explicit UndefValue(const Napi::CallbackInfo &info);

    llvm::UndefValue *getLLVMPrimitive();

private:
    llvm::UndefValue *undefValue = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};
