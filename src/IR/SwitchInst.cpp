#include "IR/IR.h"
#include "Util/Util.h"

void SwitchInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SwitchInst", {
            InstanceMethod("addCase", &SwitchInst::addCase)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("SwitchInst", func);
}

Napi::Object SwitchInst::New(Napi::Env env, llvm::SwitchInst *switchInst) {
    return constructor.New({Napi::External<llvm::SwitchInst>::New(env, switchInst)});
}

bool SwitchInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SwitchInst *SwitchInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SwitchInst::SwitchInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SwitchInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::SwitchInst>>();
    switchInst = external.Data();
}

llvm::SwitchInst *SwitchInst::getLLVMPrimitive() {
    return switchInst;
}

void SwitchInst::addCase(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen >= 2 && ConstantInt::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1])) {
        llvm::ConstantInt *onVal = ConstantInt::Extract(info[0]);
        llvm::BasicBlock *dest = BasicBlock::Extract(info[1]);
        switchInst->addCase(onVal, dest);
    } else {
        throw Napi::TypeError::New(env, ErrMsg::Class::SwitchInst::addCase);
    }
}