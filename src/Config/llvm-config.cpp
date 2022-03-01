#include "Config/llvm-config.h"

void InitLLVMConfig(Napi::Env env, Napi::Object &exports) {
    Napi::Object configNS = Napi::Object::New(env);

    configNS.Set("LLVM_DEFAULT_TARGET_TRIPLE", Napi::String::New(env, LLVM_DEFAULT_TARGET_TRIPLE));
    configNS.Set("LLVM_HOST_TRIPLE", Napi::String::New(env, LLVM_HOST_TRIPLE));
#ifdef LLVM_ON_UNIX
    configNS.Set("LLVM_ON_UNIX", Napi::Number::New(env, LLVM_ON_UNIX));
#else
    configNS.Set("LLVM_ON_UNIX", Napi::Number::New(env, 0));
#endif
    configNS.Set("LLVM_VERSION_MAJOR", Napi::Number::New(env, LLVM_VERSION_MAJOR));
    configNS.Set("LLVM_VERSION_MINOR", Napi::Number::New(env, LLVM_VERSION_MINOR));
    configNS.Set("LLVM_VERSION_PATCH", Napi::Number::New(env, LLVM_VERSION_PATCH));
    configNS.Set("LLVM_VERSION_STRING", Napi::String::New(env, LLVM_VERSION_STRING));

    exports.Set("config", configNS);
}
