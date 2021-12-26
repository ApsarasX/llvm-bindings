#include "Support/index.h"

static void InitializeAllTargetInfos(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargetInfos();
}

static void InitializeAllTargets(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargets();
}

static void InitializeAllTargetMCs(const Napi::CallbackInfo &info) {
    llvm::InitializeAllTargetMCs();
}

static void InitializeAllAsmPrinters(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmPrinters();
}

static void InitializeAllAsmParsers(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmParsers();
}

static void InitializeAllDisassemblers(const Napi::CallbackInfo &info) {
    llvm::InitializeAllDisassemblers();
}

static Napi::Value InitializeNativeTarget(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), llvm::InitializeNativeTarget());
}

static Napi::Value InitializeNativeTargetAsmPrinter(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), llvm::InitializeNativeTargetAsmPrinter());
}

static Napi::Value InitializeNativeTargetAsmParser(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), llvm::InitializeNativeTargetAsmParser());
}

static Napi::Value InitializeNativeTargetDisassembler(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), llvm::InitializeNativeTargetDisassembler());
}

void InitTargetSelect(Napi::Env env, Napi::Object &exports) {
    exports.Set(Napi::String::New(env, "InitializeAllTargetInfos"), Napi::Function::New(env, InitializeAllTargetInfos));
    exports.Set(Napi::String::New(env, "InitializeAllTargets"), Napi::Function::New(env, InitializeAllTargets));
    exports.Set(Napi::String::New(env, "InitializeAllTargetMCs"), Napi::Function::New(env, InitializeAllTargetMCs));
    exports.Set(Napi::String::New(env, "InitializeAllAsmPrinters"), Napi::Function::New(env, InitializeAllAsmPrinters));
    exports.Set(Napi::String::New(env, "InitializeAllAsmParsers"), Napi::Function::New(env, InitializeAllAsmParsers));
    exports.Set(Napi::String::New(env, "InitializeAllDisassemblers"), Napi::Function::New(env, InitializeAllDisassemblers));
    exports.Set(Napi::String::New(env, "InitializeNativeTarget"), Napi::Function::New(env, InitializeNativeTarget));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetAsmPrinter"), Napi::Function::New(env, InitializeNativeTargetAsmPrinter));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetAsmParser"), Napi::Function::New(env, InitializeNativeTargetAsmParser));
    exports.Set(Napi::String::New(env, "InitializeNativeTargetDisassembler"), Napi::Function::New(env, InitializeNativeTargetDisassembler));
}
