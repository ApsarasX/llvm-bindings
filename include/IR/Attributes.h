#pragma once

#include <napi.h>
#include <llvm/IR/Attributes.h>

class Attribute : public Napi::ObjectWrap<Attribute> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Attribute *Extract(const Napi::Value &value);

    explicit Attribute(const Napi::CallbackInfo &info);

    llvm::Attribute *getLLVMPrimitive();

private:
    llvm::Attribute attribute;
};
