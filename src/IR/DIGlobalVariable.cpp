#include "IR/IR.h"
#include "Util/Util.h"

void DIGlobalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIGlobalVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIVariable::constructor.Value());
    exports.Set("DIGlobalVariable", func);
}

Napi::Value DIGlobalVariable::New(Napi::Env env, llvm::DIGlobalVariable *variable) {
    return constructor.New({Napi::External<llvm::DIGlobalVariable>::New(env, variable)});
}

bool DIGlobalVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIGlobalVariable *DIGlobalVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIGlobalVariable::DIGlobalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIGlobalVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIGlobalVariable>>();
    variable = external.Data();
}

llvm::DIGlobalVariable *DIGlobalVariable::getLLVMPrimitive() {
    return variable;
}