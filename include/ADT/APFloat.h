#pragma once

#include <napi.h>
#include <llvm/ADT/APFloat.h>

class APFloat : public Napi::ObjectWrap<APFloat> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::APFloat &Extract(const Napi::Value &value);

    explicit APFloat(const Napi::CallbackInfo &info);

    llvm::APFloat &getLLVMPrimitive();

private:
    llvm::APFloat *apFloat = nullptr;
};
