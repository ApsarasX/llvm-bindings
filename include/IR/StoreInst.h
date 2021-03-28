#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class StoreInst : public Napi::ObjectWrap<StoreInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::StoreInst *storeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::StoreInst *Extract(const Napi::Value &value);

    explicit StoreInst(const Napi::CallbackInfo &info);

    llvm::StoreInst *getLLVMPrimitive();

private:
    llvm::StoreInst *storeInst = nullptr;

    Napi::Value getValueOperand(const Napi::CallbackInfo &info);

    Napi::Value getPointerOperand(const Napi::CallbackInfo &info);

    Napi::Value getPointerOperandType(const Napi::CallbackInfo &info);
};