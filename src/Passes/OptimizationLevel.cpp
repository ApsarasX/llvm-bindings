#include "Passes/index.h"

void OptimizationLevel::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object optimizationLevelNS = Napi::Object::New(env);
    optimizationLevelNS.Set("O0", Napi::Number::New(env, Level::O0));
    optimizationLevelNS.Set("O1", Napi::Number::New(env, Level::O1));
    optimizationLevelNS.Set("O2", Napi::Number::New(env, Level::O2));
    optimizationLevelNS.Set("O3", Napi::Number::New(env, Level::O3));
    optimizationLevelNS.Set("Os", Napi::Number::New(env, Level::Os));
    optimizationLevelNS.Set("Oz", Napi::Number::New(env, Level::Oz));
    exports.Set("OptimizationLevel", optimizationLevelNS);
}
