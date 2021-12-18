#pragma once

#include <napi.h>
#include <llvm/Bitcode/BitcodeWriter.h>

void InitBitcodeWriter(Napi::Env env, Napi::Object &exports);
