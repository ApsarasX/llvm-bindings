#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class SwitchInst : public Napi::ObjectWrap<SwitchInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::SwitchInst *switchInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SwitchInst *Extract(const Napi::Value &value);

    explicit SwitchInst(const Napi::CallbackInfo &info);

    llvm::SwitchInst *getLLVMPrimitive();

private:
    llvm::SwitchInst *switchInst = nullptr;

    void addCase(const Napi::CallbackInfo &info);
};