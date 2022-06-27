#pragma once

#include <napi.h>
#include "Support/SourceMgr.h"
#include "Support/TargetSelect.h"

void InitSupport(Napi::Env env, Napi::Object &exports);
