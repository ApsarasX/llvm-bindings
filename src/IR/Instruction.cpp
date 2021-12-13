
#include <IR/Instruction.h>

#include "IR/IR.h"
#include "Util/Util.h"

void Instruction::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Instruction", {
            InstanceMethod("use_back", &Instruction::userBack),
            InstanceMethod("getParent", &Instruction::getParent),
            InstanceMethod("getModule", &Instruction::getModule),
            InstanceMethod("getFunction", &Instruction::getFunction),
            InstanceMethod("getType", &Instruction::getType),
            InstanceMethod("setDebugLoc", &Instruction::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), User::constructor.Value());
    exports.Set("Instruction", func);
}

Napi::Value Instruction::New(Napi::Env env, llvm::Instruction *instruction) {
    if (llvm::isa<llvm::AllocaInst>(instruction)) {
        return AllocaInst::New(env, llvm::cast<llvm::AllocaInst>(instruction));
    } else if (llvm::isa<llvm::BranchInst>(instruction)) {
        return BranchInst::New(env, llvm::cast<llvm::BranchInst>(instruction));
    } else if (llvm::isa<llvm::CallInst>(instruction)) {
        return CallInst::New(env, llvm::cast<llvm::CallInst>(instruction));
    } else if (llvm::isa<llvm::InvokeInst>(instruction)) {
        return InvokeInst::New(env, llvm::cast<llvm::InvokeInst>(instruction));
    } else if (llvm::isa<llvm::LoadInst>(instruction)) {
        return LoadInst::New(env, llvm::cast<llvm::LoadInst>(instruction));
    } else if (llvm::isa<llvm::ReturnInst>(instruction)) {
        return ReturnInst::New(env, llvm::cast<llvm::ReturnInst>(instruction));
    } else if (llvm::isa<llvm::ResumeInst>(instruction)) {
        return ResumeInst::New(env, llvm::cast<llvm::ResumeInst>(instruction));
    } else if (llvm::isa<llvm::SwitchInst>(instruction)) {
        return SwitchInst::New(env, llvm::cast<llvm::SwitchInst>(instruction));
    } else if (llvm::isa<llvm::StoreInst>(instruction)) {
        return StoreInst::New(env, llvm::cast<llvm::StoreInst>(instruction));
    } else if (llvm::isa<llvm::LandingPadInst>(instruction)) {
        return LandingPadInst::New(env, llvm::cast<llvm::LandingPadInst>(instruction));
    } else if (llvm::isa<llvm::UnreachableInst>(instruction)) {
        return UnreachableInst::New(env, llvm::cast<llvm::UnreachableInst>(instruction));
    } else if (llvm::isa<llvm::PHINode>(instruction)) {
        return PHINode::New(env, llvm::cast<llvm::PHINode>(instruction));
    }
    return constructor.New({Napi::External<llvm::Instruction>::New(env, instruction)});
}

bool Instruction::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Instruction *Instruction::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Instruction::Instruction(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Instruction::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Instruction>>();
    instruction = external.Data();
}

llvm::Instruction *Instruction::getLLVMPrimitive() {
    return instruction;
}

Napi::Value Instruction::userBack(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *userInst = instruction->user_back();
    if (userInst) {
        return Instruction::New(env, userInst);
    }
    return env.Null();
}

Napi::Value Instruction::getParent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::BasicBlock *basicBlock = instruction->getParent();
    if (basicBlock) {
        return BasicBlock::New(env, basicBlock);
    }
    return env.Null();
}

Napi::Value Instruction::getModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Module *module = instruction->getModule();
    if (module) {
        return Module::New(env, module);
    }
    return env.Null();
}

Napi::Value Instruction::getFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Function *function = instruction->getFunction();
    if (function) {
        return Function::New(env, function);
    }
    return env.Null();
}

Napi::Value Instruction::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = instruction->getType();
    return Type::New(env, type);
}

void Instruction::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        instruction->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::Instruction::setDebugLoc);
}
