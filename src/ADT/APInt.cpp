#include "ADT/APInt.h"

void APInt::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Function func = DefineClass(env, "APInt", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("APInt", func);
}

bool APInt::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::APInt &APInt::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

APInt::APInt(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "APInt constructor needs to be called with new");
    }
    int argsLen = info.Length();
    if (argsLen < 2 || argsLen > 3 || !info[0].IsNumber() || !info[1].IsNumber() || (argsLen == 3 && !info[2].IsBoolean())) {
        throw Napi::TypeError::New(env, "APInt constructor needs to be called with new (numBits: unsigned, val: uint64_t, isSigned?: boolean)");
    }
    unsigned numBits = info[0].As<Napi::Number>();
    uint64_t val = info[1].As<Napi::Number>().Int64Value();
    bool isSigned = false;
    if (argsLen == 3) {
        isSigned = info[2].As<Napi::Boolean>();
    }
    apInt = new llvm::APInt(numBits, val, isSigned);
}

llvm::APInt &APInt::getLLVMPrimitive() {
    return *apInt;
}