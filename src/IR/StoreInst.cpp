#include "IR/StoreInst.h"
#include "IR/Instruction.h"
#include "IR/Value.h"
#include "IR/Type.h"
#include "Util/Inherit.h"

void StoreInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StoreInst", {
            InstanceMethod("getValueOperand", &StoreInst::getValueOperand),
            InstanceMethod("getPointerOperand", &StoreInst::getPointerOperand),
            InstanceMethod("getPointerOperandType", &StoreInst::getPointerOperandType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("StoreInst", func);
}

Napi::Object StoreInst::New(Napi::Env env, llvm::StoreInst *branchInst) {
    return constructor.New({Napi::External<llvm::StoreInst>::New(env, branchInst)});
}

bool StoreInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::StoreInst *StoreInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

StoreInst::StoreInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "StoreInst.constructor needs to be called with new");
    }
    if (info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected StoreInst pointer");
    }
    auto external = info[0].As<Napi::External<llvm::StoreInst>>();
    storeInst = external.Data();
}

llvm::StoreInst *StoreInst::getLLVMPrimitive() {
    return storeInst;
}

Napi::Value StoreInst::getValueOperand(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), storeInst->getValueOperand());
}

Napi::Value StoreInst::getPointerOperand(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), storeInst->getPointerOperand());
}

Napi::Value StoreInst::getPointerOperandType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), storeInst->getPointerOperandType());
}
