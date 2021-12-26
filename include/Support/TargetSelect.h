#pragma once

#include <napi.h>
#include <llvm/Support/TargetSelect.h>

void InitTargetSelect(Napi::Env env, Napi::Object &exports);
