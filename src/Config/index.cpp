#include "Config/index.h"

void InitConfig(Napi::Env env, Napi::Object &exports) {
    InitLLVMConfig(env, exports);
}
