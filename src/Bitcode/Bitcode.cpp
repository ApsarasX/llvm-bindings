#include "Bitcode/Bitcode.h"

void InitBitCode(Napi::Env env, Napi::Object &exports) {
    InitBitcodeWriter(env, exports);
}