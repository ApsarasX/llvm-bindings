#include "IR/IR.h"
#include "Util/Util.h"

void DIGlobalVariableExpression::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIGlobalVariableExpression", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DIGlobalVariableExpression", func);
}

Napi::Value DIGlobalVariableExpression::New(Napi::Env env, llvm::DIGlobalVariableExpression *expression) {
    return constructor.New({Napi::External<llvm::DIGlobalVariableExpression>::New(env, expression)});
}

bool DIGlobalVariableExpression::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIGlobalVariableExpression *DIGlobalVariableExpression::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIGlobalVariableExpression::DIGlobalVariableExpression(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIGlobalVariableExpression::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIGlobalVariableExpression>>();
    expression = external.Data();
}

llvm::DIGlobalVariableExpression *DIGlobalVariableExpression::getLLVMPrimitive() {
    return expression;
}