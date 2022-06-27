#include "ADT/index.h"
#include "BinaryFormat/index.h"
#include "Bitcode/index.h"
#include "Config/index.h"
#include "IR/index.h"
#include "IRReader/index.h"
#include "Linker/index.h"
#include "MC/index.h"
#include "Support/index.h"
#include "Target/index.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    InitADT(env, exports);
    InitBinaryFormat(env, exports);
    InitBitCode(env, exports);
    InitConfig(env, exports);
    InitIR(env, exports);
    InitIRReader(env, exports);
    InitLinker(env, exports);
    InitMC(env, exports);
    InitSupport(env, exports);
    InitTarget(env, exports);
    return exports;
}

NODE_API_MODULE(llvm, Init)
