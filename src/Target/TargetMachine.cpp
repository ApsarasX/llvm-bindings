#include "Target/index.h"
#include "IR/index.h"
#include "Util/index.h"

void TargetMachine::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "TargetMachine", {
            InstanceMethod("createDataLayout", &TargetMachine::createDataLayout)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("TargetMachine", func);
}

Napi::Object TargetMachine::New(Napi::Env env, llvm::TargetMachine *machine) {
    return constructor.New({Napi::External<llvm::TargetMachine>::New(env, machine)});
}

bool TargetMachine::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

TargetMachine::TargetMachine(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (info.IsConstructCall() && info.Length() == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::TargetMachine>>();
        targetMachine = external.Data();
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::TargetMachine::constructor);
}

Napi::Value TargetMachine::createDataLayout(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    const llvm::DataLayout &dataLayout = targetMachine->createDataLayout();
    return DataLayout::New(env, const_cast<llvm::DataLayout *>(&dataLayout));
}
