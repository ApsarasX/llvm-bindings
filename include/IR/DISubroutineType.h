#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DISubroutineType : public Napi::ObjectWrap<DISubroutineType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DISubroutineType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DISubroutineType *Extract(const Napi::Value &value);

    explicit DISubroutineType(const Napi::CallbackInfo &info);

    llvm::DISubroutineType *getLLVMPrimitive();

private:
    llvm::DISubroutineType *type = nullptr;
};