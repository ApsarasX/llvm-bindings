#include "BinaryFormat/index.h"

void InitBinaryFormat(Napi::Env env, Napi::Object &exports) {
    dwarf::Init(env, exports);
}
