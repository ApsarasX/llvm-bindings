#pragma once

#include <napi.h>

void Inherit(Napi::Env env, Napi::Function childCtor, Napi::Function superCtor);
