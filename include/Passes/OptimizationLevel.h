#pragma once

#include <napi.h>

namespace OptimizationLevel {
    enum Level {
        O0,
        O1,
        O2,
        O3,
        Os,
        Oz,
    };

    void Init(Napi::Env env, Napi::Object &exports);
}
