#pragma once

#include <napi.h>
#include <llvm/MC/TargetRegistry.h>

class Target : public Napi::ObjectWrap<Target> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Target *target);

    explicit Target(const Napi::CallbackInfo &info);

private:
    const llvm::Target *target = nullptr;

    Napi::Value createTargetMachine(const Napi::CallbackInfo &info);

    Napi::Value getName(const Napi::CallbackInfo &info);

    Napi::Value getShortDescription(const Napi::CallbackInfo &info);
};

void InitTargetRegistry(Napi::Env env, Napi::Object &exports);
