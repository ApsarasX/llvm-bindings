#pragma once

#include <napi.h>
#include <llvm/IR/Function.h>

class Function : public Napi::ObjectWrap<Function> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Function *function);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Function *Extract(const Napi::Value &value);

    explicit Function(const Napi::CallbackInfo &info);

    llvm::Function *getLLVMPrimitive();

private:
    llvm::Function *function = nullptr;

    static Napi::Value create(const Napi::CallbackInfo &info);

    Napi::Value argSize(const Napi::CallbackInfo &info);

    Napi::Value getArg(const Napi::CallbackInfo &info);

    Napi::Value getReturnType(const Napi::CallbackInfo &info);

    void addBasicBlock(const Napi::CallbackInfo &info);

    Napi::Value getEntryBlock(const Napi::CallbackInfo &info);

    Napi::Value getExitBlock(const Napi::CallbackInfo &info);

    void insertAfter(const Napi::CallbackInfo &info);

    void deleteBody(const Napi::CallbackInfo &info);

    void removeFromParent(const Napi::CallbackInfo &info);

    void eraseFromParent(const Napi::CallbackInfo &info);

    Napi::Value useEmpty(const Napi::CallbackInfo &info);

    Napi::Value userEmpty(const Napi::CallbackInfo &info);
};