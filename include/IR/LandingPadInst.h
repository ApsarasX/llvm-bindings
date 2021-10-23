#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class LandingPadInst : public Napi::ObjectWrap<LandingPadInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::LandingPadInst *lpInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::LandingPadInst *Extract(const Napi::Value &value);

    explicit LandingPadInst(const Napi::CallbackInfo &info);

    llvm::LandingPadInst *getLLVMPrimitive();

private:
    llvm::LandingPadInst *lpInst = nullptr;

    void setCleanup(const Napi::CallbackInfo &info);

    void addClause(const Napi::CallbackInfo &info);
};