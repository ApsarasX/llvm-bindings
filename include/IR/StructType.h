#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class StructType : public Napi::ObjectWrap<StructType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::StructType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::StructType *Extract(const Napi::Value &value);

    explicit StructType(const Napi::CallbackInfo &info);

    llvm::StructType *getLLVMPrimitive();

private:
    llvm::StructType *structType = nullptr;

    static Napi::Value create(const Napi::CallbackInfo &info);

    static Napi::Value get(const Napi::CallbackInfo &info);

    void setBody(const Napi::CallbackInfo &info);

    Napi::Value getPointerTo(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);
};