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
    } else if (llvm::isa<llvm::FenceInst>(inst)) {
        return FenceInst::New(env, llvm::cast<llvm::FenceInst>(inst));
    } else if (llvm::isa<llvm::AtomicCmpXchgInst>(inst)) {
        return AtomicCmpXchgInst::New(env, llvm::cast<llvm::AtomicCmpXchgInst>(inst));
    } else if (llvm::isa<llvm::AtomicRMWInst>(inst)) {
        return AtomicRMWInst::New(env, llvm::cast<llvm::AtomicRMWInst>(inst));
    } else if (llvm::isa<llvm::GetElementPtrInst>(inst)) {
        return GetElementPtrInst::New(env, llvm::cast<llvm::GetElementPtrInst>(inst));
    } else if (llvm::isa<llvm::ICmpInst>(inst)) {
        return ICmpInst::New(env, llvm::cast<llvm::ICmpInst>(inst));
    } else if (llvm::isa<llvm::FCmpInst>(inst)) {
        return FCmpInst::New(env, llvm::cast<llvm::FCmpInst>(inst));
    } else if (llvm::isa<llvm::CallInst>(inst)) {
        return CallInst::New(env, llvm::cast<llvm::CallInst>(inst));
    } else if (llvm::isa<llvm::SelectInst>(inst)) {
        return SelectInst::New(env, llvm::cast<llvm::SelectInst>(inst));
    } else if (llvm::isa<llvm::VAArgInst>(inst)) {
        return VAArgInst::New(env, llvm::cast<llvm::VAArgInst>(inst));
    } else if (llvm::isa<llvm::ExtractElementInst>(inst)) {
        return ExtractElementInst::New(env, llvm::cast<llvm::ExtractElementInst>(inst));
    } else if (llvm::isa<llvm::InsertElementInst>(inst)) {
        return InsertElementInst::New(env, llvm::cast<llvm::InsertElementInst>(inst));
    } else if (llvm::isa<llvm::ShuffleVectorInst>(inst)) {
        return ShuffleVectorInst::New(env, llvm::cast<llvm::ShuffleVectorInst>(inst));
    } else if (llvm::isa<llvm::ExtractValueInst>(inst)) {
        return ExtractValueInst::New(env, llvm::cast<llvm::ExtractValueInst>(inst));
    } else if (llvm::isa<llvm::InsertValueInst>(inst)) {
        return InsertValueInst::New(env, llvm::cast<llvm::InsertValueInst>(inst));
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
    } else if (llvm::isa<llvm::IndirectBrInst>(inst)) {
        return IndirectBrInst::New(env, llvm::cast<llvm::IndirectBrInst>(inst));
    } else if (llvm::isa<llvm::InvokeInst>(inst)) {
        return InvokeInst::New(env, llvm::cast<llvm::InvokeInst>(inst));
    } else if (llvm::isa<llvm::CallBrInst>(inst)) {
        return CallBrInst::New(env, llvm::cast<llvm::CallBrInst>(inst));
    } else if (llvm::isa<llvm::ResumeInst>(inst)) {
        return ResumeInst::New(env, llvm::cast<llvm::ResumeInst>(inst));
    } else if (llvm::isa<llvm::CatchSwitchInst>(inst)) {
        return CatchSwitchInst::New(env, llvm::cast<llvm::CatchSwitchInst>(inst));
    } else if (llvm::isa<llvm::CleanupPadInst>(inst)) {
        return CleanupPadInst::New(env, llvm::cast<llvm::CleanupPadInst>(inst));
    } else if (llvm::isa<llvm::CatchPadInst>(inst)) {
        return CatchPadInst::New(env, llvm::cast<llvm::CatchPadInst>(inst));
    } else if (llvm::isa<llvm::CatchReturnInst>(inst)) {
        return CatchReturnInst::New(env, llvm::cast<llvm::CatchReturnInst>(inst));
    } else if (llvm::isa<llvm::CleanupReturnInst>(inst)) {
        return CleanupReturnInst::New(env, llvm::cast<llvm::CleanupReturnInst>(inst));
    } else if (llvm::isa<llvm::UnreachableInst>(inst)) {
        return UnreachableInst::New(env, llvm::cast<llvm::UnreachableInst>(inst));
    } else if (llvm::isa<llvm::TruncInst>(inst)) {
        return TruncInst::New(env, llvm::cast<llvm::TruncInst>(inst));
    } else if (llvm::isa<llvm::ZExtInst>(inst)) {
        return ZExtInst::New(env, llvm::cast<llvm::ZExtInst>(inst));
    } else if (llvm::isa<llvm::SExtInst>(inst)) {
        return SExtInst::New(env, llvm::cast<llvm::SExtInst>(inst));
    } else if (llvm::isa<llvm::FPTruncInst>(inst)) {
        return FPTruncInst::New(env, llvm::cast<llvm::FPTruncInst>(inst));
    } else if (llvm::isa<llvm::FPExtInst>(inst)) {
        return FPExtInst::New(env, llvm::cast<llvm::FPExtInst>(inst));
    } else if (llvm::isa<llvm::UIToFPInst>(inst)) {
        return UIToFPInst::New(env, llvm::cast<llvm::UIToFPInst>(inst));
    } else if (llvm::isa<llvm::SIToFPInst>(inst)) {
        return SIToFPInst::New(env, llvm::cast<llvm::SIToFPInst>(inst));
    } else if (llvm::isa<llvm::FPToUIInst>(inst)) {
        return FPToUIInst::New(env, llvm::cast<llvm::FPToUIInst>(inst));
    } else if (llvm::isa<llvm::FPToSIInst>(inst)) {
        return FPToSIInst::New(env, llvm::cast<llvm::FPToSIInst>(inst));
    } else if (llvm::isa<llvm::IntToPtrInst>(inst)) {
        return IntToPtrInst::New(env, llvm::cast<llvm::IntToPtrInst>(inst));
    } else if (llvm::isa<llvm::PtrToIntInst>(inst)) {
        return PtrToIntInst::New(env, llvm::cast<llvm::PtrToIntInst>(inst));
    } else if (llvm::isa<llvm::BitCastInst>(inst)) {
        return BitCastInst::New(env, llvm::cast<llvm::BitCastInst>(inst));
    } else if (llvm::isa<llvm::AddrSpaceCastInst>(inst)) {
        return AddrSpaceCastInst::New(env, llvm::cast<llvm::AddrSpaceCastInst>(inst));
    } else if (llvm::isa<llvm::FreezeInst>(inst)) {
        return FreezeInst::New(env, llvm::cast<llvm::FreezeInst>(inst));
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
