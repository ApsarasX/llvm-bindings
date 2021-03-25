#include "Target/Target.h"
#include "Target/TargetMachine.h"

void InitTarget(Napi::Env env, Napi::Object& exports) {
    TargetMachine::Init(env, exports);
}
