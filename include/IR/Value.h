#pragma once

#include <napi.h>
#include <llvm/IR/Value.h>

class Value : public Napi::ObjectWrap<Value> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::Value *value);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Value *Extract(const Napi::Value &value);

    explicit Value(const Napi::CallbackInfo &info);

    llvm::Value *getLLVMPrimitive();

private:
    llvm::Value *value = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    Napi::Value hasName(const Napi::CallbackInfo &info);

    Napi::Value getName(const Napi::CallbackInfo &info);

    void setName(const Napi::CallbackInfo &info);

    void deleteValue(const Napi::CallbackInfo &info);

    void replaceAllUsesWith(const Napi::CallbackInfo &info);

    Napi::Value useEmpty(const Napi::CallbackInfo &info);

    Napi::Value userEmpty(const Napi::CallbackInfo &info);
};