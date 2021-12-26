#pragma once

#include <napi.h>
#include <llvm/Target/TargetMachine.h>

class TargetMachine : public Napi::ObjectWrap<TargetMachine> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::TargetMachine *machine);

    static bool IsClassOf(const Napi::Value &value);

    explicit TargetMachine(const Napi::CallbackInfo &info);

private:
    const llvm::TargetMachine *targetMachine = nullptr;

    Napi::Value createDataLayout(const Napi::CallbackInfo &info);
};
