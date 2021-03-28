#pragma once

#include <napi.h>

#include "ADT/APInt.h"
#include "ADT/APFloat.h"

void InitADT(Napi::Env env, Napi::Object &exports);