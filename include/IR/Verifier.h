#pragma once

#include <napi.h>
#include <llvm/IR/Verifier.h>

void InitVerifier(Napi::Env env, Napi::Object &exports);