#include "Support/index.h"

void InitSupport(Napi::Env env, Napi::Object &exports) {
    SMDiagnostic::Init(env, exports);
    InitTargetSelect(env, exports);
    CodeGen::Init(env, exports);
}
