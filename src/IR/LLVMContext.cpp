#include "IR/index.h"
#include "Util/index.h"

void LLVMContext::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "LLVMContext", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("LLVMContext", func);
}

bool LLVMContext::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::LLVMContext &LLVMContext::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

LLVMContext::LLVMContext(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::LLVMContext::constructor);
    }
    context = new llvm::LLVMContext();
}

llvm::LLVMContext &LLVMContext::getLLVMPrimitive() {
    return *context;
}
