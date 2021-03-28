#include "IR/ConstantFP.h"
#include "IR/Constant.h"
#include "IR/LLVMContext.h"
#include "IR/Type.h"
#include "ADT/APFloat.h"
#include "Util/Inherit.h"
#include "Util/ErrMsg.h"

void ConstantFP::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantFP", {
            StaticMethod("get", &ConstantFP::get),
            StaticMethod("getNaN", &ConstantFP::getNaN)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantFP", func);
}

Napi::Object ConstantFP::New(Napi::Env env, llvm::ConstantFP *constantFP) {
    return constructor.New({Napi::External<llvm::ConstantFP>::New(env, constantFP)});
}

bool ConstantFP::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantFP *ConstantFP::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantFP::ConstantFP(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantFP::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantFP>>();
    constantFP = external.Data();
}

llvm::ConstantFP *ConstantFP::getLLVMPrimitive() {
    return constantFP;
}

Napi::Value ConstantFP::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 2) {
        if (Type::IsClassOf(info[0])) {
            llvm::Type *type = Type::Extract(info[0]);
            llvm::Constant *result = nullptr;
            if (info[1].IsNumber()) {
                double value = info[1].As<Napi::Number>();
                result = llvm::ConstantFP::get(type, value);
            } else if (APFloat::IsClassOf(info[1])) {
                llvm::APFloat &value = APFloat::Extract(info[1]);
                result = llvm::ConstantFP::get(type, value);
            } else if (info[1].IsString()) {
                std::string value = info[1].As<Napi::String>();
                result = llvm::ConstantFP::get(type, value);
            }
            if (result) {
                return Constant::New(env, result);
            }
        } else if (LLVMContext::IsClassOf(info[0]) && APFloat::IsClassOf(info[1])) {
            llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
            llvm::APFloat &value = APFloat::Extract(info[1]);
            llvm::ConstantFP *result = llvm::ConstantFP::get(context, value);
            return ConstantFP::New(env, result);
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ConstantFP::get);
}

Napi::Value ConstantFP::getNaN(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && Type::IsClassOf(info[0])) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Constant *nan = llvm::ConstantFP::getNaN(type);
        return Constant::New(env, nan);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ConstantFP::getNaN);
}
