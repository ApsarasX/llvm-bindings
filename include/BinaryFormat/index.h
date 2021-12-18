#pragma once

#include <napi.h>
#include "BinaryFormat/Dwarf.h"

void InitBinaryFormat(Napi::Env env, Napi::Object &exports);
