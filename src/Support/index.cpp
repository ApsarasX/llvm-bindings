#include "Support/index.h"

void InitSupport(Napi::Env env, Napi::Object &exports) {
    exports.Set(Napi::String::New(env, "InitializeAllTargetInfos"), Napi::Function::New(env, InitializeAllTargetInfos));
    exports.Set(Napi::String::New(env, "InitializeAllTargets"), Napi::Function::New(env, InitializeAllTargets));
    exports.Set(Napi::String::New(env, "InitializeAllTargetMCs"), Napi::Function::New(env, InitializeAllTargetMCs));
    exports.Set(Napi::String::New(env, "InitializeAllAsmParsers"), Napi::Function::New(env, InitializeAllAsmParsers));
    exports.Set(Napi::String::New(env, "InitializeAllAsmPrinters"), Napi::Function::New(env, InitializeAllAsmPrinters));
    InitTargetRegistry(env, exports);
    SMDiagnostic::Init(env, exports);
    Target::Init(env, exports);
}
