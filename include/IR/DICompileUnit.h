#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DICompileUnit : public Napi::ObjectWrap<DICompileUnit> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DICompileUnit *unit);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DICompileUnit *Extract(const Napi::Value &value);

    explicit DICompileUnit(const Napi::CallbackInfo &info);

    llvm::DICompileUnit *getLLVMPrimitive();

private:
    llvm::DICompileUnit *unit = nullptr;

    Napi::Value getFile(const Napi::CallbackInfo &info);
};