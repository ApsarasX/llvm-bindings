#include "IR/IR.h"
#include "Util/Util.h"

void StructType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StructType", {
            StaticMethod("create", &StructType::create),
            InstanceMethod("setBody", &StructType::setBody),
            InstanceMethod("getPointerTo", &StructType::getPointerTo),
            InstanceMethod("isStructTy", &StructType::isStructTy)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("StructType", func);
}

Napi::Object StructType::New(Napi::Env env, llvm::StructType *type) {
    return constructor.New({Napi::External<llvm::StructType>::New(env, type)});
}

bool StructType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::StructType *StructType::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

StructType::StructType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::StructType>>();
    structType = external.Data();
}


llvm::StructType *StructType::getLLVMPrimitive() {
    return structType;
}

Napi::Value StructType::create(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (!(argsLen == 2 && LLVMContext::IsClassOf(info[0]) && info[1].IsString()) &&
        !(argsLen >= 3 && LLVMContext::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsString())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::create);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    const std::string &name = info[argsLen == 2 ? 1 : 2].As<Napi::String>();
    llvm::StructType *structType;
    if (argsLen >= 3) {
        auto eleTypesArray = info[1].As<Napi::Array>();
        int numElements = eleTypesArray.Length();
        std::vector<llvm::Type *> elementTypes(numElements);
        for (int i = 0; i < numElements; ++i) {
            elementTypes[i] = Type::Extract(eleTypesArray.Get(i));
        }
        structType = llvm::StructType::create(context, elementTypes, name);
    } else {
        structType = llvm::StructType::create(context, name);
    }
    return StructType::New(env, structType);
}

void StructType::setBody(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsArray()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::setBody);
    }
    auto eleTypesArray = info[0].As<Napi::Array>();
    int numElements = eleTypesArray.Length();
    std::vector<llvm::Type *> elementTypes(numElements);
    for (int i = 0; i < numElements; ++i) {
        elementTypes[i] = Type::Extract(eleTypesArray.Get(i));
    }
    structType->setBody(elementTypes);
}

Napi::Value StructType::getPointerTo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::getPointerTo);
    }
    unsigned addrSpace = 0;
    if (info.Length() >= 1) {
        addrSpace = info[0].As<Napi::Number>();
    }
    llvm::PointerType *pointerType = structType->getPointerTo(addrSpace);
    return PointerType::New(env, pointerType);
}

Napi::Value StructType::isStructTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), structType->isStructTy());
}