#pragma once

#include <napi.h>
#include <llvm/IR/Argument.h>

class Argument : public Napi::ObjectWrap<Argument> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Argument *argument);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Argument *Extract(const Napi::Value &value);

    explicit Argument(const Napi::CallbackInfo &info);

    llvm::Argument *getLLVMPrimitive();

private:
    llvm::Argument *argument = nullptr;

    Napi::Value getParent(const Napi::CallbackInfo &info);

    Napi::Value getArgNo(const Napi::CallbackInfo &info);
};