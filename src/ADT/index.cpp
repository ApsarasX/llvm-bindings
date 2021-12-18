#include "ADT/index.h"

void InitADT(Napi::Env env, Napi::Object &exports) {
    APInt::Init(env, exports);
    APFloat::Init(env, exports);
}
