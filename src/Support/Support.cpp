#include <llvm/Support/TargetSelect.h>

#include "Support/Support.h"

void InitializeAllTargetInfos(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargetInfos();
}

void InitializeAllTargets(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargets();
}

void InitializeAllTargetMCs(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargetMCs();
}

void InitializeAllAsmParsers(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmParsers();
}

void InitializeAllAsmPrinters(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmPrinters();
}

void InitSupport(Napi::Env env, Napi::Object &exports) {
    exports.Set(Napi::String::New(env, "initializeAllTargetInfos"), Napi::Function::New(env, InitializeAllTargetInfos));
    exports.Set(Napi::String::New(env, "initializeAllTargets"), Napi::Function::New(env, InitializeAllTargets));
    exports.Set(Napi::String::New(env, "initializeAllTargetMCs"), Napi::Function::New(env, InitializeAllTargetMCs));
    exports.Set(Napi::String::New(env, "initializeAllAsmParsers"), Napi::Function::New(env, InitializeAllAsmParsers));
    exports.Set(Napi::String::New(env, "initializeAllAsmPrinters"), Napi::Function::New(env, InitializeAllAsmPrinters));
    InitTargetRegistry(env, exports);
    SMDiagnostic::Init(env, exports);
    Target::Init(env, exports);
}