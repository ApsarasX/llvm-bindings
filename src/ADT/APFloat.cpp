#include "ADT/APFloat.h"

void APFloat::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Function func = DefineClass(env, "APFloat", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("APFloat", func);
}

bool APFloat::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::APFloat &APFloat::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

APFloat::APFloat(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "APFloat constructor needs to be called with new");
    }
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, "APFloat constructor needs to be called with new (value: number)");
    }
    double value = info[0].As<Napi::Number>();
    apFloat = new llvm::APFloat(value);
}

llvm::APFloat &APFloat::getLLVMPrimitive() {
    return *apFloat;
}