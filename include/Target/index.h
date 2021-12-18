#pragma once

#include <napi.h>
#include "Target/TargetMachine.h"

void InitTarget(Napi::Env env, Napi::Object &exports);
