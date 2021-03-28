#pragma once

#include <napi.h>

#include "Bitcode/BitcodeWriter.h"

void InitBitCode(Napi::Env env, Napi::Object &exports);
