#include "ADT/ADT.h"
#include "ADT/APInt.h"
#include "ADT/APFloat.h"

void InitADT(Napi::Env env, Napi::Object &exports) {
    APInt::Init(env, exports);
    APFloat::Init(env, exports);
}