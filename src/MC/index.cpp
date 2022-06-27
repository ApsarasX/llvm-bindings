#include "MC/index.h"

void InitMC(Napi::Env env, Napi::Object &exports) {
    Target::Init(env, exports);
    InitTargetRegistry(env, exports);
}
