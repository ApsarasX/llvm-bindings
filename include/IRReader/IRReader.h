#pragma once

#include <napi.h>
#include <llvm/IRReader/IRReader.h>

Napi::Value parseIRFile(const Napi::CallbackInfo &info);
