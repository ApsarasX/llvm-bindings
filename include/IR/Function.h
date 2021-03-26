#pragma once

#include <napi.h>
#include <llvm/IR/Function.h>

class Function : public Napi::ObjectWrap<Function> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Function *function);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Function *Extract(const Napi::Value &value);

    explicit Function(const Napi::CallbackInfo &info);

    llvm::Function *getLLVMPrimitive();

private:
    llvm::Function *function = nullptr;

    static Napi::Value create(const Napi::CallbackInfo &info);

    Napi::Value argSize(const Napi::CallbackInfo &info);

    Napi::Value getArg(const Napi::CallbackInfo &info);
};