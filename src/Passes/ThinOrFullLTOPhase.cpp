#include "Passes/index.h"

#include "llvm/Pass.h"

void ThinOrFullLTOPhase::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object ltoPhaseNS = Napi::Object::New(env);
    ltoPhaseNS.Set("None", Napi::Number::New(env, (unsigned) llvm::ThinOrFullLTOPhase::None));
    ltoPhaseNS.Set("ThinLTOPreLink", Napi::Number::New(env, (unsigned) llvm::ThinOrFullLTOPhase::ThinLTOPreLink));
    ltoPhaseNS.Set("ThinLTOPostLink", Napi::Number::New(env, (unsigned) llvm::ThinOrFullLTOPhase::ThinLTOPostLink));
    ltoPhaseNS.Set("FullLTOPreLink", Napi::Number::New(env, (unsigned) llvm::ThinOrFullLTOPhase::FullLTOPreLink));
    ltoPhaseNS.Set("FullLTOPostLink", Napi::Number::New(env, (unsigned) llvm::ThinOrFullLTOPhase::FullLTOPostLink));
    exports.Set("ThinOrFullLTOPhase", ltoPhaseNS);
}
