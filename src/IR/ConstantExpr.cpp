#include "IR/IR.h"
#include "Util/Util.h"

void ConstantExpr::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantExpr", {
            // TODO: need more methods by use of factory mode
            StaticMethod("getBitCast", &ConstantExpr::getBitCast),
            InstanceMethod("getType", &ConstantExpr::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantExpr", func);
}

Napi::Object ConstantExpr::New(Napi::Env env, llvm::ConstantExpr *constantExpr) {
    return constructor.New({Napi::External<llvm::ConstantExpr>::New(env, constantExpr)});
}

bool ConstantExpr::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantExpr *ConstantExpr::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantExpr::ConstantExpr(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantExpr::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantExpr>>();
    constantExpr = external.Data();
}

llvm::ConstantExpr *ConstantExpr::getLLVMPrimitive() {
    return constantExpr;
}

Napi::Value ConstantExpr::getBitCast(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && Constant::IsClassOf(info[0]) && Type::IsClassOf(info[1])) {
        llvm::Constant *constant = Constant::Extract(info[0]);
        llvm::Type *type = Type::Extract(info[1]);
        return Constant::New(env, llvm::ConstantExpr::getBitCast(constant, type));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ConstantExpr::getBitCast);
}

Napi::Value ConstantExpr::getType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), constantExpr->getType());
}

