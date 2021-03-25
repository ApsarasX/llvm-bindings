#include "Util/Inherit.h"

void Inherit(Napi::Env env, Napi::Function childCtor, Napi::Function superCtor) {
    Napi::Object global = env.Global();
    Napi::Object Object = global.Get("Object").As<Napi::Object>(); // NOLINT
    Napi::Function setPrototypeOf = Object.Get("setPrototypeOf").As<Napi::Function>(); // NOLINT

    Napi::Value childProto = childCtor.Get("prototype");
    Napi::Value superProto = superCtor.Get("prototype");

    setPrototypeOf.Call({childProto, superProto});
    setPrototypeOf.Call({childCtor, superCtor});
}