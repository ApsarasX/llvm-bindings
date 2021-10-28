#pragma once

#include <napi.h>
#include <llvm/IR/Type.h>

class Type : public Napi::ObjectWrap<Type> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Type *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Type *Extract(const Napi::Value &value);

    explicit Type(const Napi::CallbackInfo &info);

    llvm::Type *getLLVMPrimitive();

private:
    llvm::Type *type = nullptr;

    static Napi::Value getIntNTy(const Napi::CallbackInfo &info);

    Napi::Value getPointerTo(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);

    Napi::Value getPrimitiveSizeInBits(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);

    typedef bool (llvm::Type::*isTypeFn)() const;

    template<isTypeFn method>
    Napi::Value isTypeFactory(const Napi::CallbackInfo &info) {
        return Napi::Boolean::New(info.Env(), (type->*method)());
    }

    static Napi::Value isSameType(const Napi::CallbackInfo &info);
};