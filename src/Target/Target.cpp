#include "Target/Target.h"

void InitTarget(Napi::Env env, Napi::Object &exports) {
    TargetMachine::Init(env, exports);
}
