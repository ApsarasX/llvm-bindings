#pragma once

#include <napi.h>
#include <llvm/IR/GlobalValue.h>

class GlobalValue : public Napi::ObjectWrap<GlobalValue> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::GlobalValue *globalValue);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::GlobalValue *Extract(const Napi::Value &value);

    explicit GlobalValue(const Napi::CallbackInfo &info);

    llvm::GlobalValue *getLLVMPrimitive();

private:
    llvm::GlobalValue *globalValue = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);
};
