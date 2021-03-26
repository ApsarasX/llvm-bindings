#include "ADT/ADT.h"
#include "Bitcode/Bitcode.h"
#include "IR/IR.h"
#include "Support/Support.h"
#include "Target/Target.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    InitADT(env, exports);
    InitBitCode(env, exports);
    InitIR(env, exports);
    InitSupport(env, exports);
    InitTarget(env, exports);
    return exports;
}

NODE_API_MODULE(llvm, Init)