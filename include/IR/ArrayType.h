#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class ArrayType : public Napi::ObjectWrap<ArrayType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ArrayType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ArrayType *Extract(const Napi::Value &value);

    explicit ArrayType(const Napi::CallbackInfo &info);

    llvm::ArrayType *getLLVMPrimitive();

private:
    llvm::ArrayType *arrayType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    static Napi::Value isValidElementType(const Napi::CallbackInfo &info);

    Napi::Value getNumElements(const Napi::CallbackInfo &info);

    Napi::Value getElementType(const Napi::CallbackInfo &info);
};