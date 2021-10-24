#pragma once

#include <napi.h>
#include <llvm/IR/Instructions.h>

class ResumeInst : public Napi::ObjectWrap<ResumeInst> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ResumeInst *resumeInst);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ResumeInst *Extract(const Napi::Value &value);

    explicit ResumeInst(const Napi::CallbackInfo &info);

    llvm::ResumeInst *getLLVMPrimitive();

private:
    llvm::ResumeInst *resumeInst = nullptr;
};