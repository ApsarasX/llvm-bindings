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

void InitializeAllAsmPrinters(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmPrinters();
}

void InitializeAllAsmParsers(const Napi::CallbackInfo &info) {
    llvm::InitializeAllAsmParsers();
}

void InitializeAllDisassemblers(const Napi::CallbackInfo &info) {
    llvm::InitializeAllDisassemblers();
}

void InitializeNativeTarget(const Napi::CallbackInfo &info) {
    llvm::InitializeNativeTarget();
}

void InitializeNativeTargetAsmPrinter(const Napi::CallbackInfo &info) {
    llvm::InitializeNativeTargetAsmPrinter();
}

void InitializeNativeTargetAsmParser(const Napi::CallbackInfo &info) {
    llvm::InitializeNativeTargetAsmParser();
}

void InitializeNativeTargetDisassembler(const Napi::CallbackInfo &info) {
    llvm::InitializeNativeTargetDisassembler();
}
