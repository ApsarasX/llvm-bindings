#pragma once

#include <napi.h>
#include <llvm/Support/SourceMgr.h>

class SMDiagnostic : public Napi::ObjectWrap<SMDiagnostic> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::SMDiagnostic &Extract(const Napi::Value &value);

    explicit SMDiagnostic(const Napi::CallbackInfo &info);

    llvm::SMDiagnostic &getLLVMPrimitive();

private:
    llvm::SMDiagnostic *diagnostic = nullptr;
};
