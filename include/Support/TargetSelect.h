#pragma once

#include <napi.h>
#include <llvm/Support/TargetSelect.h>

void InitializeAllTargetInfos(const Napi::CallbackInfo &info);

void InitializeAllTargets(const Napi::CallbackInfo &info);

void InitializeAllTargetMCs(const Napi::CallbackInfo &info);

void InitializeAllAsmPrinters(const Napi::CallbackInfo &info);

void InitializeAllAsmParsers(const Napi::CallbackInfo &info);

void InitializeAllDisassemblers(const Napi::CallbackInfo &info);

void InitializeNativeTarget(const Napi::CallbackInfo &info);

void InitializeNativeTargetAsmPrinter(const Napi::CallbackInfo &info);

void InitializeNativeTargetAsmParser(const Napi::CallbackInfo &info);

void InitializeNativeTargetDisassembler(const Napi::CallbackInfo &info);
