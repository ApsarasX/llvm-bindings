#include "IR/IR.h"
#include "Util/Util.h"

void ArrayType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ArrayType", {
            StaticMethod("get", &ArrayType::get),
            StaticMethod("isValidElementType", &ArrayType::isValidElementType),
            InstanceMethod("getNumElements", &ArrayType::getNumElements),
            InstanceMethod("getElementType", &ArrayType::getElementType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("ArrayType", func);
}

Napi::Object ArrayType::New(Napi::Env env, llvm::ArrayType *type) {
    return constructor.New({Napi::External<llvm::ArrayType>::New(env, type)});
}

bool ArrayType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ArrayType *ArrayType::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ArrayType::ArrayType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ArrayType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ArrayType>>();
    arrayType = external.Data();
}

llvm::ArrayType *ArrayType::getLLVMPrimitive() {
    return arrayType;
}

Napi::Value ArrayType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 2 && Type::IsClassOf(info[0]) && info[1].IsNumber()) {
        llvm::Type *elemType = Type::Extract(info[0]);
        unsigned numElements = info[1].As<Napi::Number>();
        return ArrayType::New(env, llvm::ArrayType::get(elemType, numElements));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ArrayType::get);
}

Napi::Value ArrayType::isValidElementType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && Type::IsClassOf(info[0])) {
        llvm::Type *elemType = Type::Extract(info[0]);
        return Napi::Boolean::New(env, llvm::ArrayType::isValidElementType(elemType));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ArrayType::isValidElementType);
}

Napi::Value ArrayType::getNumElements(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), arrayType->getNumElements());
}

Napi::Value ArrayType::getElementType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), arrayType->getElementType());
}
