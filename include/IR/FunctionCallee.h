#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class FunctionCallee : public Napi::ObjectWrap<FunctionCallee> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionCallee &Extract(const Napi::Value &value);

    explicit FunctionCallee(const Napi::CallbackInfo &info);

    llvm::FunctionCallee &getLLVMPrimitive();

private:
    llvm::FunctionCallee *functionCallee = nullptr;

    Napi::Value getFunctionType(const Napi::CallbackInfo &info);

    Napi::Value getCallee(const Napi::CallbackInfo &info);
};