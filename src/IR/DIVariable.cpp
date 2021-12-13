#include "IR/IR.h"
#include "Util/Util.h"

void DIVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DINode::constructor.Value());
    exports.Set("DIVariable", func);
}

Napi::Value DIVariable::New(Napi::Env env, llvm::DIVariable *variable) {
    if (llvm::isa<llvm::DILocalVariable>(variable)) {
        return DILocalVariable::New(env, llvm::cast<llvm::DILocalVariable>(variable));
    } else if (llvm::isa<llvm::DIGlobalVariable>(variable)) {
        return DIGlobalVariable::New(env, llvm::cast<llvm::DIGlobalVariable>(variable));
    }
    return constructor.New({Napi::External<llvm::DIVariable>::New(env, variable)});
}

bool DIVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIVariable *DIVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIVariable::DIVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIVariable>>();
    variable = external.Data();
}

llvm::DIVariable *DIVariable::getLLVMPrimitive() {
    return variable;
}