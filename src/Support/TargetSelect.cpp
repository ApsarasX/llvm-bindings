#include "Support/index.h"

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
