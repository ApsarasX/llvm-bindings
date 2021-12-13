#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DILexicalBlock : public Napi::ObjectWrap<DILexicalBlock> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILexicalBlock *block);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILexicalBlock *Extract(const Napi::Value &value);

    explicit DILexicalBlock(const Napi::CallbackInfo &info);

    llvm::DILexicalBlock *getLLVMPrimitive();

private:
    llvm::DILexicalBlock *block = nullptr;
};