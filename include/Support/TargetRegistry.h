#pragma once

#include <napi.h>
#include <llvm/Support/TargetRegistry.h>

void InitTargetRegistry(Napi::Env env, Napi::Object &exports);