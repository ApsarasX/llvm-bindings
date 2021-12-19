#include "Support/index.h"

void InitSupport(Napi::Env env, Napi::Object &exports) {
//    exports.Set(Napi::String::New(env, "InitializeAllTargetInfos"), Napi::Function::New(env, InitializeAllTargetInfos));
//    exports.Set(Napi::String::New(env, "InitializeAllTargets"), Napi::Function::New(env, InitializeAllTargets));
//    exports.Set(Napi::String::New(env, "InitializeAllTargetMCs"), Napi::Function::New(env, InitializeAllTargetMCs));
//    exports.Set(Napi::String::New(env, "InitializeAllAsmPrinters"), Napi::Function::New(env, InitializeAllAsmPrinters));
//    exports.Set(Napi::String::New(env, "InitializeAllAsmParsers"), Napi::Function::New(env, InitializeAllAsmParsers));
//    exports.Set(Napi::String::New(env, "InitializeAllDisassemblers"), Napi::Function::New(env, InitializeAllDisassemblers));
    exports.Set(Napi::String::New(env, "InitializeNativeTarget"), Napi::Function::New(env, InitializeNativeTarget));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetAsmPrinter"), Napi::Function::New(env, InitializeNativeTargetAsmPrinter));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetAsmParser"), Napi::Function::New(env, InitializeNativeTargetAsmParser));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetDisassembler"), Napi::Function::New(env, InitializeNativeTargetDisassembler));
    InitTargetRegistry(env, exports);
    SMDiagnostic::Init(env, exports);
    Target::Init(env, exports);
}
