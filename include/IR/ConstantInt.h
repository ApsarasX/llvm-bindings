#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantInt : public Napi::ObjectWrap<ConstantInt> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantInt *constantInt);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantInt *Extract(const Napi::Value &value);

    explicit ConstantInt(const Napi::CallbackInfo &info);

    llvm::ConstantInt *getLLVMPrimitive();

private:
    llvm::ConstantInt *constantInt = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};
