#include "Linker/index.h"

void InitLinker(Napi::Env env, Napi::Object &exports) {
    Linker::Init(env, exports);
}
