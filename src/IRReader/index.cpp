#include "IRReader/index.h"

void InitIRReader(Napi::Env env, Napi::Object &exports) {
    exports.Set("parseIRFile", Napi::Function::New(env, parseIRFile));
}
