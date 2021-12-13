#include "IR/IR.h"
#include "Util/Util.h"

void DIExpression::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIExpression", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DIExpression", func);
}

Napi::Value DIExpression::New(Napi::Env env, llvm::DIExpression *expression) {
    return constructor.New({Napi::External<llvm::DIExpression>::New(env, expression)});
}

bool DIExpression::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIExpression *DIExpression::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIExpression::DIExpression(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIExpression::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIExpression>>();
    expression = external.Data();
}

llvm::DIExpression *DIExpression::getLLVMPrimitive() {
    return expression;
}