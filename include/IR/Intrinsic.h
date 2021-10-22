#pragma once

#include <napi.h>
#include <llvm/IR/Intrinsics.h>

namespace Intrinsic {
    void Init(Napi::Env env, Napi::Object &exports);
}