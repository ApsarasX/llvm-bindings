#include "IR/IR.h"
#include "Util/Util.h"

void CallInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "CallInst", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("CallInst", func);
}

Napi::Object CallInst::New(Napi::Env env, llvm::CallInst *callInst) {
    return constructor.New({Napi::External<llvm::CallInst>::New(env, callInst)});
}

bool CallInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::CallInst *CallInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

CallInst::CallInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::CallInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::CallInst>>();
    callInst = external.Data();
}

llvm::CallInst *CallInst::getLLVMPrimitive() {
    return callInst;
}
