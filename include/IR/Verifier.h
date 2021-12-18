#pragma once

#include <napi.h>
#include <llvm/IR/Verifier.h>

namespace Verifier {
    void Init(Napi::Env env, Napi::Object &exports);
}
