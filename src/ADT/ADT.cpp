#include "ADT/ADT.h"

void InitADT(Napi::Env env, Napi::Object &exports) {
    APInt::Init(env, exports);
    APFloat::Init(env, exports);
}