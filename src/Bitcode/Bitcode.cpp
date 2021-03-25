#include "Bitcode/Bitcode.h"
#include "Bitcode/BitcodeWriter.h"

void InitBitCode(Napi::Env env, Napi::Object& exports) {
    InitBitcodeWriter(env, exports);
}