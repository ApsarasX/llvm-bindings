#include "IR/IR.h"
#include "Util/Util.h"

void DILocalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DILocalVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIVariable::constructor.Value());
    exports.Set("DILocalVariable", func);
}

Napi::Value DILocalVariable::New(Napi::Env env, llvm::DILocalVariable *variable) {
    return constructor.New({Napi::External<llvm::DILocalVariable>::New(env, variable)});
}

bool DILocalVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILocalVariable *DILocalVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILocalVariable::DILocalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILocalVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILocalVariable>>();
    variable = external.Data();
}

llvm::DILocalVariable *DILocalVariable::getLLVMPrimitive() {
    return variable;
}