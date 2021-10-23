#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class FunctionCallee : public Napi::ObjectWrap<FunctionCallee> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FunctionCallee callee);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionCallee Extract(const Napi::Value &value);

    explicit FunctionCallee(const Napi::CallbackInfo &info);

    llvm::FunctionCallee getLLVMPrimitive();

private:
    static inline llvm::FunctionCallee tmpCallee; // tmp in static-new

    llvm::FunctionCallee callee;

    Napi::Value getFunctionType(const Napi::CallbackInfo &info);

    Napi::Value getCallee(const Napi::CallbackInfo &info);
};
