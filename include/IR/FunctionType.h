#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class FunctionType : public Napi::ObjectWrap<FunctionType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FunctionType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionType *Extract(const Napi::Value &value);

    explicit FunctionType(const Napi::CallbackInfo &info);

    llvm::FunctionType *getLLVMPrimitive();

private:
    llvm::FunctionType *functionType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};