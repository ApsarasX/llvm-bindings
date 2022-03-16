#pragma once

#include <napi.h>
#include <llvm/IR/GlobalObject.h>

class GlobalObject : public Napi::ObjectWrap<GlobalObject> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::GlobalObject *globalObject);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::GlobalObject *Extract(const Napi::Value &value);

    explicit GlobalObject(const Napi::CallbackInfo &info);

    llvm::GlobalObject *getLLVMPrimitive();

private:
    llvm::GlobalObject *globalObject = nullptr;

    Napi::Value getType(const Napi::CallbackInfo &info);

    Napi::Value getValueType(const Napi::CallbackInfo &info);
};
