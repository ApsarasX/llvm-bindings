#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantPointerNull : public Napi::ObjectWrap<ConstantPointerNull> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantPointerNull *constantPointerNull);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantPointerNull *Extract(const Napi::Value &value);

    explicit ConstantPointerNull(const Napi::CallbackInfo &info);

    llvm::ConstantPointerNull *getLLVMPrimitive();

private:
    llvm::ConstantPointerNull *constantPointerNull = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};
