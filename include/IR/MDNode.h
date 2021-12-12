#pragma once

#include <napi.h>
#include <llvm/IR/Metadata.h>

class MDNode : public Napi::ObjectWrap<MDNode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::MDNode *node);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::MDNode *Extract(const Napi::Value &value);

    explicit MDNode(const Napi::CallbackInfo &info);

    llvm::MDNode *getLLVMPrimitive();

private:
    llvm::MDNode *node = nullptr;
};