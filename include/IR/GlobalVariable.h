#pragma once

#include <napi.h>
#include <llvm/IR/GlobalVariable.h>

class GlobalVariable : public Napi::ObjectWrap<GlobalVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::GlobalVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::GlobalVariable *Extract(const Napi::Value &value);

    explicit GlobalVariable(const Napi::CallbackInfo &info);

    llvm::GlobalVariable *getLLVMPrimitive();

private:
    llvm::GlobalVariable *globalVariable = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    Napi::Value getValueType(const Napi::CallbackInfo &info);

    void removeFromParent(const Napi::CallbackInfo &info);

    void eraseFromParent(const Napi::CallbackInfo &info);

    void addDebugInfo(const Napi::CallbackInfo &info);
};
