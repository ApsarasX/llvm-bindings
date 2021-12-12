#include "IR/IR.h"
#include "Util/Util.h"

void FunctionCallee::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FunctionCallee", {
            InstanceMethod("getFunctionType", &FunctionCallee::getFunctionType),
            InstanceMethod("getCallee", &FunctionCallee::getCallee)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FunctionCallee", func);
}

Napi::Object FunctionCallee::New(Napi::Env env, llvm::FunctionCallee callee) {
    tmpCallee = callee;
    return constructor.New({});
}

bool FunctionCallee::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionCallee FunctionCallee::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionCallee::FunctionCallee(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionCallee::constructor);
    }
    if (tmpCallee) {
        callee = tmpCallee;
        tmpCallee = llvm::FunctionCallee(nullptr);
    }
}

llvm::FunctionCallee FunctionCallee::getLLVMPrimitive() {
    return callee;
}

Napi::Value FunctionCallee::getFunctionType(const Napi::CallbackInfo &info) {
    return FunctionType::New(info.Env(), callee.getFunctionType());
}

Napi::Value FunctionCallee::getCallee(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), callee.getCallee());
}
