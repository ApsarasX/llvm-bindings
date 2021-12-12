#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DISubprogram : public Napi::ObjectWrap<DISubprogram> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DISubprogram *subProgram);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DISubprogram *Extract(const Napi::Value &value);

    explicit DISubprogram(const Napi::CallbackInfo &info);

    llvm::DISubprogram *getLLVMPrimitive();

private:
    llvm::DISubprogram *subprogram = nullptr;
};