#pragma once

#include <napi.h>
#include <llvm/Linker/Linker.h>

class Linker : public Napi::ObjectWrap<Linker> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    explicit Linker(const Napi::CallbackInfo &info);

private:
    Napi::Value linkInModule(const Napi::CallbackInfo &info);

    static Napi::Value linkModules(const Napi::CallbackInfo &info);

    llvm::Linker *linker = nullptr;
};
