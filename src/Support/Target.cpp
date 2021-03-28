#include "Support/Support.h"
#include "Target/Target.h"
#include "Util/Util.h"

void Target::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Target", {
            InstanceMethod("createTargetMachine", &Target::createTargetMachine),
            InstanceMethod("getName", &Target::getName),
            InstanceMethod("getShortDescription", &Target::getShortDescription)
    });
    constructor = Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Target", func);
}

Napi::Object Target::New(Napi::Env env, llvm::Target *target) {
    return constructor.New({Napi::External<llvm::Target>::New(env, target)});
}

Target::Target(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Target>{info} {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Target::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Target>>();
    target = external.Data();
}


Napi::Value Target::createTargetMachine(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen < 2 || !info[0].IsString() || !info[1].IsString() || argsLen >= 3 && !info[2].IsString()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Target::createTargetMachine);
    }
    std::string targetTriple = info[0].As<Napi::String>();
    std::string cpu = info[1].As<Napi::String>();
    std::string features;
    if (argsLen >= 3) {
        features = info[2].As<Napi::String>();
    }
    llvm::TargetOptions options{};
    llvm::TargetMachine *targetMachinePtr = target->createTargetMachine(targetTriple, cpu, features, options, llvm::Optional<llvm::Reloc::Model>{});
    return TargetMachine::New(env, targetMachinePtr);
}

Napi::Value Target::getName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, target->getName());
}

Napi::Value Target::getShortDescription(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, target->getShortDescription());
}