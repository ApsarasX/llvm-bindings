#pragma once

#include <napi.h>
#include <llvm/IRReader/IRReader.h>

void InitIRReader(Napi::Env env, Napi::Object &exports);