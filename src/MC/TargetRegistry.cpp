#include "MC/index.h"
#include "Target/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
//                        Target Class
//===----------------------------------------------------------------------===//

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
    if (info.IsConstructCall() && info.Length() == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::Target>>();
        target = external.Data();
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Target::constructor);
}

bool isCreateTargetDefaultArgs(const Napi::CallbackInfo &info, unsigned argsLen) {
    return argsLen == 2 && info[0].IsString() && info[1].IsString()
        || argsLen == 2 && info[0].IsString() && info[1].IsString() && info[2].IsString();
}

bool isCreateTargetRelocArgs(const Napi::CallbackInfo &info, unsigned argsLen) {
    return argsLen == 4 && info[0].IsString() && info[1].IsString() && info[2].IsString() && info[3].IsNumber();
}

bool isCreateTargetCodeModelArgs(const Napi::CallbackInfo &info, unsigned argsLen) {
    return argsLen == 5
        && info[0].IsString()
        && info[1].IsString()
        && info[2].IsString()
        && info[3].IsNumber()
        && info[4].IsNumber();
}

bool isCreateTargetCodeGenOptArgs(const Napi::CallbackInfo &info, unsigned argsLen) {
    return argsLen == 6
        && info[0].IsString()
        && info[1].IsString()
        && info[2].IsString()
        && info[3].IsNumber()
        && info[4].IsNumber()
        && info[5].IsNumber();
}

bool isCreateTargetJitArgs(const Napi::CallbackInfo &info, unsigned argsLen) {
    return argsLen == 7
        && info[0].IsString()
        && info[1].IsString()
        && info[2].IsString()
        && info[3].IsNumber()
        && info[4].IsNumber()
        && info[5].IsNumber()
        && info[6].IsBoolean();
}

Napi::Value Target::createTargetMachine(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();

    auto isCreateTargetDefault = isCreateTargetDefaultArgs(info, argsLen);
    auto isCreateTargetReloc = isCreateTargetRelocArgs(info, argsLen);
    auto isCreateTargetCodeModel = isCreateTargetCodeModelArgs(info, argsLen);
    auto isCreateTargetCodeGenOpt = isCreateTargetCodeGenOptArgs(info, argsLen);
    auto isCreateTargetJit = isCreateTargetJitArgs(info, argsLen);

    auto isValidCall = isCreateTargetDefault
        || isCreateTargetReloc
        || isCreateTargetCodeModel
        || isCreateTargetCodeGenOpt
        || isCreateTargetJit;

    if (!isValidCall) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Target::createTargetMachine);
    }

    std::string targetTriple = info[0].As<Napi::String>();
    std::string cpu = info[1].As<Napi::String>();
    std::string features;

    if (argsLen >= 3) {
        features = info[2].As<Napi::String>();
    }

    if (isCreateTargetReloc) {
        llvm::Optional<llvm::Reloc::Model> relocModel = (llvm::Reloc::Model) info[3].As<Napi::Number>().Uint32Value();
        llvm::TargetOptions options{};
        llvm::TargetMachine *targetMachinePtr = target->createTargetMachine(targetTriple, cpu, features, options, relocModel);
        return TargetMachine::New(env, targetMachinePtr);
    }

    if (isCreateTargetCodeModel) {
        llvm::Optional<llvm::Reloc::Model> relocModel = (llvm::Reloc::Model) info[3].As<Napi::Number>().Uint32Value();
        llvm::Optional<llvm::CodeModel::Model> codeModel = (llvm::CodeModel::Model) info[4].As<Napi::Number>().Uint32Value();
        llvm::TargetOptions options{};
        llvm::TargetMachine *targetMachinePtr = target->createTargetMachine(targetTriple, cpu, features, options, relocModel, codeModel);
        return TargetMachine::New(env, targetMachinePtr);
    }

    if (isCreateTargetCodeGenOpt) {
        llvm::Optional<llvm::Reloc::Model> relocModel = (llvm::Reloc::Model) info[3].As<Napi::Number>().Uint32Value();
        llvm::Optional<llvm::CodeModel::Model> codeModel = (llvm::CodeModel::Model) info[4].As<Napi::Number>().Uint32Value();
        auto codeGenOpt = (llvm::CodeGenOpt::Level) info[4].As<Napi::Number>().Uint32Value();
        llvm::TargetOptions options{};
        llvm::TargetMachine *targetMachinePtr = target->createTargetMachine(targetTriple, cpu, features, options, relocModel, codeModel, codeGenOpt);
        return TargetMachine::New(env, targetMachinePtr);
    }

    llvm::Optional<llvm::Reloc::Model> relocModel{};
    llvm::TargetOptions options{};
    llvm::TargetMachine *targetMachinePtr = target->createTargetMachine(targetTriple, cpu, features, options, relocModel);
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

//===----------------------------------------------------------------------===//
//                        TargetRegistry Namespace
//===----------------------------------------------------------------------===//

// TODO: implement class TargetRegistry

static Napi::Value lookupTarget(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsString()) {
        std::string triple = info[0].As<Napi::String>();
        std::string error;
        const llvm::Target *result = llvm::TargetRegistry::lookupTarget(triple, error);
        if (result) {
            return Target::New(env, const_cast<llvm::Target *>(result));
        } else {
            llvm::errs() << error + '\n';
            return env.Null();
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::TargetRegistry::lookupTarget);
}

void InitTargetRegistry(Napi::Env env, Napi::Object &exports) {
    Napi::Object targetRegistryNS = Napi::Object::New(env);
    targetRegistryNS.Set("lookupTarget", Napi::Function::New(env, lookupTarget));
    exports.Set("TargetRegistry", targetRegistryNS);
}
