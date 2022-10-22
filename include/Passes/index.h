#pragma once

#include <napi.h>
#include "Passes/OptimizationLevel.h"
#include "Passes/ThinOrFullLTOPhase.h"

void InitPasses(Napi::Env env, Napi::Object &exports);
