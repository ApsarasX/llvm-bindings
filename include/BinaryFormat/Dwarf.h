#pragma once

#include <napi.h>
#include <llvm/BinaryFormat/Dwarf.h>

namespace dwarf {
    void Init(Napi::Env env, Napi::Object &exports);
}
