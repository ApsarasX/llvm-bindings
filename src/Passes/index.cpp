#include "Passes/index.h"

void InitPasses(Napi::Env env, Napi::Object &exports) {
    OptimizationLevel::Init(env, exports);
    ThinOrFullLTOPhase::Init(env, exports);
}
