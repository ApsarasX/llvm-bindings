#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantStruct : public Napi::ObjectWrap<ConstantStruct> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantStruct *constantStruct);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantStruct *Extract(const Napi::Value &value);

    explicit ConstantStruct(const Napi::CallbackInfo &info);

    llvm::ConstantStruct *getLLVMPrimitive();

private:
    llvm::ConstantStruct *constantStruct = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};
