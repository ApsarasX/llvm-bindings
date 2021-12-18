#pragma once

#include <napi.h>
#include <llvm/IR/Metadata.h>

class Metadata : public Napi::ObjectWrap<Metadata> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::Metadata *metadata);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Metadata *Extract(const Napi::Value &value);

    explicit Metadata(const Napi::CallbackInfo &info);

    llvm::Metadata *getLLVMPrimitive();

private:
    llvm::Metadata *metadata = nullptr;
};

class MDNode : public Napi::ObjectWrap<MDNode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::MDNode *node);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::MDNode *Extract(const Napi::Value &value);

    explicit MDNode(const Napi::CallbackInfo &info);

    llvm::MDNode *getLLVMPrimitive();

private:
    llvm::MDNode *node = nullptr;
};

namespace LLVMConstants {
    void Init(Napi::Env env, Napi::Object &exports);
}
