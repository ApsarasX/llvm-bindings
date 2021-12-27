#pragma once

#include <napi.h>
#include <llvm/IR/DataLayout.h>

class DataLayout : public Napi::ObjectWrap<DataLayout> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::DataLayout *dl);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DataLayout &Extract(const Napi::Value &value);

    explicit DataLayout(const Napi::CallbackInfo &info);

    llvm::DataLayout &getLLVMPrimitive();

private:
    llvm::DataLayout *dataLayout = nullptr;

    Napi::Value getStringRepresentation(const Napi::CallbackInfo &info);

    Napi::Value getTypeAllocSize(const Napi::CallbackInfo &info);
};
