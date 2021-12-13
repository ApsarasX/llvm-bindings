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

namespace LLVMConstants {
    void Init(Napi::Env env, Napi::Object &exports);
}
