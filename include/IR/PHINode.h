#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class PHINode : public Napi::ObjectWrap<PHINode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::PHINode *phiNode);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::PHINode *Extract(const Napi::Value &value);

    explicit PHINode(const Napi::CallbackInfo &info);

    llvm::PHINode *getLLVMPrimitive();

private:
    llvm::PHINode *phiNode = nullptr;

    void addIncoming(const Napi::CallbackInfo &info);

    void setDebugLoc(const Napi::CallbackInfo &info);
};