#pragma once

#include <napi.h>
#include <llvm/Config/llvm-config.h>

void InitLLVMConfig(Napi::Env env, Napi::Object &exports);
