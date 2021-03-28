#include "IR/Type.h"
#include "IR/PointerType.h"
#include "Util/Inherit.h"
#include "Util/ErrMsg.h"

void PointerType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PointerType", {
            StaticMethod("get", &PointerType::get),
            InstanceMethod("getElementType", &PointerType::getElementType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("PointerType", func);
}

Napi::Object PointerType::New(Napi::Env env, llvm::PointerType *type) {
    return constructor.New({Napi::External<llvm::PointerType>::New(env, type)});
}

bool PointerType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::PointerType *PointerType::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

PointerType::PointerType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PointerType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::PointerType>>();
    pointerType = external.Data();
}

Napi::Value PointerType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !Type::IsClassOf(info[0]) || !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PointerType::get);
    }
    llvm::Type *type = Type::Extract(info[0]);
    uint32_t addrSpace = info[1].As<Napi::Number>();
    llvm::PointerType *pointerType = llvm::PointerType::get(type, addrSpace);
    return PointerType::New(env, pointerType);
}

Napi::Value PointerType::getElementType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *elementType = pointerType->getElementType();
    return Type::New(env, elementType);
}

llvm::PointerType *PointerType::getLLVMPrimitive() {
    return pointerType;
}
