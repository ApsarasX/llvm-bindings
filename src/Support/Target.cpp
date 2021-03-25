#include "Support/Target.h"
#include "Target/TargetMachine.h"

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
    auto argsLength = info.Length();

    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Target constructor needs to be called with new");
    }

    if (argsLength < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Target constructor needs to be called with a pointer to a Target");
    }

    auto external = info[0].As<Napi::External<llvm::Target>>();
    this->target = external.Data();
}


Napi::Value Target::createTargetMachine(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsString() || !info[1].IsString()) {
        throw Napi::TypeError::New(env, "Function needs to be called at least with the arguments: triple: string, cpu: string.");
    }

    std::string targetTriple = info[0].As<Napi::String>();
    std::string cpu = info[1].As<Napi::String>();
    std::string features;

    if (info.Length() > 2) {
        if (info[2].IsString()) {
            features = info[2].As<Napi::String>();
        } else {
            throw Napi::TypeError::New(env, "The 3th argument New createTargetMachine needs to be a string");
        }
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