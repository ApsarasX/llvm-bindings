#pragma once

#include <napi.h>
#include "Linker/Linker.h"

void InitLinker(Napi::Env env, Napi::Object &exports);
