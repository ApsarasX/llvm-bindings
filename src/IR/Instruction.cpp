#include "IR/index.h"
#include "Util/index.h"

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

Napi::Value Instruction::New(Napi::Env env, llvm::Instruction *inst) {
    if (llvm::isa<llvm::AllocaInst>(inst)) {
        return AllocaInst::New(env, llvm::cast<llvm::AllocaInst>(inst));
    } else if (llvm::isa<llvm::LoadInst>(inst)) {
        return LoadInst::New(env, llvm::cast<llvm::LoadInst>(inst));
    } else if (llvm::isa<llvm::StoreInst>(inst)) {
        return StoreInst::New(env, llvm::cast<llvm::StoreInst>(inst));
    } else if (llvm::isa<llvm::GetElementPtrInst>(inst)) {
        return GetElementPtrInst::New(env, llvm::cast<llvm::GetElementPtrInst>(inst));
    } else if (llvm::isa<llvm::CallInst>(inst)) {
        return CallInst::New(env, llvm::cast<llvm::CallInst>(inst));
    } else if (llvm::isa<llvm::PHINode>(inst)) {
        return PHINode::New(env, llvm::cast<llvm::PHINode>(inst));
    } else if (llvm::isa<llvm::LandingPadInst>(inst)) {
        return LandingPadInst::New(env, llvm::cast<llvm::LandingPadInst>(inst));
    } else if (llvm::isa<llvm::ReturnInst>(inst)) {
        return ReturnInst::New(env, llvm::cast<llvm::ReturnInst>(inst));
    } else if (llvm::isa<llvm::BranchInst>(inst)) {
        return BranchInst::New(env, llvm::cast<llvm::BranchInst>(inst));
    } else if (llvm::isa<llvm::SwitchInst>(inst)) {
        return SwitchInst::New(env, llvm::cast<llvm::SwitchInst>(inst));
    } else if (llvm::isa<llvm::InvokeInst>(inst)) {
        return InvokeInst::New(env, llvm::cast<llvm::InvokeInst>(inst));
    } else if (llvm::isa<llvm::ResumeInst>(inst)) {
        return ResumeInst::New(env, llvm::cast<llvm::ResumeInst>(inst));
    } else if (llvm::isa<llvm::UnreachableInst>(inst)) {
        return UnreachableInst::New(env, llvm::cast<llvm::UnreachableInst>(inst));
    }
    return constructor.New({Napi::External<llvm::Instruction>::New(env, inst)});
}

bool Instruction::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
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
    inst = external.Data();
}

llvm::Instruction *Instruction::getLLVMPrimitive() {
    return inst;
}

Napi::Value Instruction::userBack(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *userInst = inst->user_back();
    if (userInst) {
        return Instruction::New(env, userInst);
    }
    return env.Null();
}

Napi::Value Instruction::getParent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::BasicBlock *basicBlock = inst->getParent();
    if (basicBlock) {
        return BasicBlock::New(env, basicBlock);
    }
    return env.Null();
}

Napi::Value Instruction::getModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Module *module = inst->getModule();
    if (module) {
        return Module::New(env, module);
    }
    return env.Null();
}

Napi::Value Instruction::getFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Function *function = inst->getFunction();
    if (function) {
        return Function::New(env, function);
    }
    return env.Null();
}

Napi::Value Instruction::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = inst->getType();
    return Type::New(env, type);
}

void Instruction::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        inst->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::Instruction::setDebugLoc);
}
