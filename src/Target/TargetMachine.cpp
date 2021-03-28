#include <llvm/Target/TargetMachine.h>

#include "Target/TargetMachine.h"
#include "Util/ErrMsg.h"

void TargetMachine::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "TargetMachine", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("TargetMachine", func);
}

Napi::Object TargetMachine::New(Napi::Env env, llvm::TargetMachine *machine) {
    return constructor.New({Napi::External<llvm::TargetMachine>::New(env, machine)});
}

bool TargetMachine::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

TargetMachine::TargetMachine(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::TargetMachine::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::TargetMachine>>();
    targetMachine = external.Data();
}
