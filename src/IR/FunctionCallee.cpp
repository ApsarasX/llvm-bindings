#include "IR/FunctionCallee.h"
#include "IR/FunctionType.h"
#include "IR/Value.h"

void FunctionCallee::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Function func = DefineClass(env, "FunctionCallee", {
            InstanceMethod("getFunctionType", &FunctionCallee::getFunctionType),
            InstanceMethod("getCallee", &FunctionCallee::getCallee)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FunctionCallee", func);
}

bool FunctionCallee::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionCallee &FunctionCallee::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionCallee::FunctionCallee(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "FunctionCallee constructor needs to be called with new");
    }
    int argsLen = info.Length();
    if (argsLen < 2 || !FunctionType::IsClassOf(info[0]) || !Value::IsClassOf(info[1])) {
        throw Napi::TypeError::New(env, "FunctionCallee constructor needs to be called with new (funcType: FunctionType, callee: Value)");
    }
    llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
    llvm::Value *callee = Value::Extract(info[1]);
    functionCallee = new llvm::FunctionCallee(funcType, callee);
}

llvm::FunctionCallee &FunctionCallee::getLLVMPrimitive() {
    return *functionCallee;
}

Napi::Value FunctionCallee::getFunctionType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return FunctionType::New(env, functionCallee->getFunctionType());
}

Napi::Value FunctionCallee::getCallee(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Value::New(env, functionCallee->getCallee());
}
