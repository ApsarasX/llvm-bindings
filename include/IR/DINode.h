#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DINode : public Napi::ObjectWrap<DINode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DINode *node);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DINode *Extract(const Napi::Value &value);

    explicit DINode(const Napi::CallbackInfo &info);

    llvm::DINode *getLLVMPrimitive();

private:
    llvm::DINode *node = nullptr;
};