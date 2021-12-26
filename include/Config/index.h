#pragma once

#include <napi.h>
#include "Config/llvm-config.h"

void InitConfig(Napi::Env env, Napi::Object &exports);
