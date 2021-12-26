#include "Support/index.h"

void InitSupport(Napi::Env env, Napi::Object &exports) {
    SMDiagnostic::Init(env, exports);
    Target::Init(env, exports);
    InitTargetRegistry(env, exports);
    InitTargetSelect(env, exports);
}
