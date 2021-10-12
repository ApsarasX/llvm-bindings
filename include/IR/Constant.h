#pragma once

#include <napi.h>
#include <llvm/IR/Constant.h>

class Constant : public Napi::ObjectWrap<Constant> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Constant *constant);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Constant *Extract(const Napi::Value &value);

    explicit Constant(const Napi::CallbackInfo &info);

    llvm::Constant *getLLVMPrimitive();

private:
    llvm::Constant *constant = nullptr;

    static Napi::Value getNullValue(const Napi::CallbackInfo &info);

    static Napi::Value getAllOnesValue(const Napi::CallbackInfo &info);

    Napi::Value isNullValue(const Napi::CallbackInfo &info);

    Napi::Value isOneValue(const Napi::CallbackInfo &info);

    Napi::Value isAllOnesValue(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};
