#include "ADT/index.h"
#include "Util/index.h"

void APInt::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "APInt", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("APInt", func);
}

bool APInt::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::APInt &APInt::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

APInt::APInt(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (!info.IsConstructCall() || argsLen < 2 || !info[0].IsNumber() || !(info[1].IsNumber() || info[1].IsBigInt()) || argsLen >= 3 && !info[2].IsBoolean()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::APInt::constructor);
    }
    unsigned numBits = info[0].As<Napi::Number>();
    bool lossless = true;
    uint64_t val = info[1].IsNumber()
        ? info[1].As<Napi::Number>().Int64Value()
        : info[1].As<Napi::BigInt>().Int64Value(&lossless);
    bool isSigned = false;
    if (argsLen >= 3) {
        isSigned = info[2].As<Napi::Boolean>();
    }
    apInt = new llvm::APInt(numBits, val, isSigned);
}

llvm::APInt &APInt::getLLVMPrimitive() {
    return *apInt;
}
