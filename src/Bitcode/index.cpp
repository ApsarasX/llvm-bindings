#include "Bitcode/index.h"

void InitBitCode(Napi::Env env, Napi::Object &exports) {
    InitBitcodeWriter(env, exports);
}
