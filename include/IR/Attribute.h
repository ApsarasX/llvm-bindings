#pragma once

#include <napi.h>
#include <llvm/IR/Attributes.h>

namespace attribute {
    void Init(Napi::Env env, Napi::Object &exports);

    llvm::Attribute::AttrKind Extract(const Napi::Value &value);
}
