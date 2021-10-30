#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class PointerType : public Napi::ObjectWrap<PointerType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::PointerType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::PointerType *Extract(const Napi::Value &value);

    explicit PointerType(const Napi::CallbackInfo &info);

    llvm::PointerType *getLLVMPrimitive();

private:
    llvm::PointerType *pointerType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    static Napi::Value getUnqual(const Napi::CallbackInfo &info);

    Napi::Value getElementType(const Napi::CallbackInfo &info);

    Napi::Value isPointerTy(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);

    Napi::Value getPointerElementType(const Napi::CallbackInfo &info);
};