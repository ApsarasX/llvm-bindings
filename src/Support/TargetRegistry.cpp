#include "Support/TargetRegistry.h"
#include "Support/Target.h"
#include "Target/TargetMachine.h"

Napi::Value lookupTarget(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "lookupTarget needs to be called with a single string argument");
    }

    std::string triple = info[0].As<Napi::String>();
    std::string error{};

    const llvm::Target *result = llvm::TargetRegistry::lookupTarget(triple, error);

    if (!result) {
        std::string msg = "Failed to lookup Target: " + error;
        throw Napi::Error::New(env, msg);
    }

    return Target::New(env, const_cast<llvm::Target *>(result));
}

void InitTargetRegistry(Napi::Env env, Napi::Object &exports) {
    Napi::Object targetRegistry = Napi::Object::New(env);
    targetRegistry.Set("lookupTarget", Napi::Function::New(env, &lookupTarget));

    exports.Set("TargetRegistry", targetRegistry);
}
