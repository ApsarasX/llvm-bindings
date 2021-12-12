#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DIBasicType : public Napi::ObjectWrap<DIBasicType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIBasicType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIBasicType *Extract(const Napi::Value &value);

    explicit DIBasicType(const Napi::CallbackInfo &info);

    llvm::DIBasicType *getLLVMPrimitive();

private:
    llvm::DIBasicType *type = nullptr;
};