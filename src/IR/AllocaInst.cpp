#include "IR/IR.h"
#include "Util/Util.h"

void AllocaInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "AllocaInst", {
            InstanceMethod("getAllocatedType", &AllocaInst::getAllocatedType),
            InstanceMethod("getArraySize", &AllocaInst::getArraySize),
            InstanceMethod("getType", &AllocaInst::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("AllocaInst", func);
}

Napi::Object AllocaInst::New(Napi::Env env, llvm::AllocaInst *allocaInst) {
    return constructor.New({Napi::External<llvm::AllocaInst>::New(env, allocaInst)});
}

bool AllocaInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::AllocaInst *AllocaInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

AllocaInst::AllocaInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::AllocaInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::AllocaInst>>();
    allocaInst = external.Data();
}

llvm::AllocaInst *AllocaInst::getLLVMPrimitive() {
    return allocaInst;
}

Napi::Value AllocaInst::getAllocatedType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), allocaInst->getAllocatedType());
}

Napi::Value AllocaInst::getArraySize(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), allocaInst->getArraySize());
}

Napi::Value AllocaInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = allocaInst->getType();
    return Type::New(env, type);
}
