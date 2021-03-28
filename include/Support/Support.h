#pragma once

#include <napi.h>

#include "Support/SMDiagnostic.h"
#include "Support/Target.h"
#include "Support/TargetRegistry.h"

void InitSupport(Napi::Env env, Napi::Object &exports);