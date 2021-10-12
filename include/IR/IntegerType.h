#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class IntegerType : public Napi::ObjectWrap<IntegerType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::IntegerType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::IntegerType *Extract(const Napi::Value &value);

    explicit IntegerType(const Napi::CallbackInfo &info);

    llvm::IntegerType *getLLVMPrimitive();

private:
    llvm::IntegerType *integerType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);
};