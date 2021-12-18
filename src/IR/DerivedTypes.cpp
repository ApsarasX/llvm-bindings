#include "IR/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
// class IntegerType
//===----------------------------------------------------------------------===//

void IntegerType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IntegerType", {
            StaticMethod("get", &IntegerType::get),
            InstanceMethod("isStructTy", &IntegerType::isStructTy),
            InstanceMethod("isIntegerTy", &IntegerType::isIntegerTy),
            InstanceMethod("isVoidTy", &IntegerType::isVoidTy),
            InstanceMethod("getTypeID", &IntegerType::getTypeID)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("IntegerType", func);
}

Napi::Object IntegerType::New(Napi::Env env, llvm::IntegerType *type) {
    return constructor.New({Napi::External<llvm::IntegerType>::New(env, type)});
}

bool IntegerType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::IntegerType *IntegerType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IntegerType::IntegerType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntegerType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::IntegerType>>();
    integerType = external.Data();
}

llvm::IntegerType *IntegerType::getLLVMPrimitive() {
    return integerType;
}

Napi::Value IntegerType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !LLVMContext::IsClassOf(info[0]) || !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntegerType::get);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    unsigned numBits = info[1].As<Napi::Number>();
    llvm::IntegerType *integerType = llvm::IntegerType::get(context, numBits);
    return IntegerType::New(env, integerType);
}

Napi::Value IntegerType::isStructTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), integerType->isStructTy());
}

Napi::Value IntegerType::isIntegerTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntegerType::isIntegerTy);
    }
    bool result = info.Length() == 0 ? integerType->isIntegerTy() : integerType->isIntegerTy(info[0].As<Napi::Number>());
    return Napi::Boolean::New(env, result);
}

Napi::Value IntegerType::isVoidTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), integerType->isVoidTy());
}

Napi::Value IntegerType::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), integerType->getTypeID());
}

//===----------------------------------------------------------------------===//
// class FunctionType
//===----------------------------------------------------------------------===//

void FunctionType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FunctionType", {
            StaticMethod("get", &FunctionType::get),
            InstanceMethod("isVoidTy", &FunctionType::isVoidTy),
            InstanceMethod("getTypeID", &FunctionType::getTypeID)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("FunctionType", func);
}

Napi::Object FunctionType::New(Napi::Env env, llvm::FunctionType *type) {
    return constructor.New({Napi::External<llvm::FunctionType>::New(env, type)});
}

bool FunctionType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionType *FunctionType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionType::FunctionType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FunctionType>>();
    functionType = external.Data();
}

llvm::FunctionType *FunctionType::getLLVMPrimitive() {
    return functionType;
}

Napi::Value FunctionType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (!(argsLen == 2 && Type::IsClassOf(info[0]) && info[1].IsBoolean()) &&
        !(argsLen >= 3 && Type::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsBoolean())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionType::get);
    }
    llvm::Type *returnType = Type::Extract(info[0]);
    bool isVarArg = info[argsLen == 2 ? 1 : 2].As<Napi::Boolean>();
    llvm::FunctionType *functionType;
    if (argsLen >= 3) {
        auto paramsArray = info[1].As<Napi::Array>();
        unsigned numParams = paramsArray.Length();
        std::vector<llvm::Type *> paramTypes(numParams);
        for (unsigned i = 0; i < numParams; ++i) {
            paramTypes[i] = Type::Extract(paramsArray.Get(i));
        }
        functionType = llvm::FunctionType::get(returnType, paramTypes, isVarArg);
    } else {
        functionType = llvm::FunctionType::get(returnType, isVarArg);
    }
    return FunctionType::New(env, functionType);
}

Napi::Value FunctionType::isVoidTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), functionType->isVoidTy());
}

Napi::Value FunctionType::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), functionType->getTypeID());
}

//===----------------------------------------------------------------------===//
// class FunctionCallee
//===----------------------------------------------------------------------===//

void FunctionCallee::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FunctionCallee", {
            InstanceMethod("getFunctionType", &FunctionCallee::getFunctionType),
            InstanceMethod("getCallee", &FunctionCallee::getCallee)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FunctionCallee", func);
}

Napi::Object FunctionCallee::New(Napi::Env env, llvm::FunctionCallee callee) {
    tmpCallee = callee;
    return constructor.New({});
}

bool FunctionCallee::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionCallee FunctionCallee::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionCallee::FunctionCallee(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionCallee::constructor);
    }
    if (tmpCallee) {
        callee = tmpCallee;
        tmpCallee = llvm::FunctionCallee(nullptr);
    }
}

llvm::FunctionCallee FunctionCallee::getLLVMPrimitive() {
    return callee;
}

Napi::Value FunctionCallee::getFunctionType(const Napi::CallbackInfo &info) {
    return FunctionType::New(info.Env(), callee.getFunctionType());
}

Napi::Value FunctionCallee::getCallee(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), callee.getCallee());
}

//===----------------------------------------------------------------------===//
// class StructType
//===----------------------------------------------------------------------===//

void StructType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "StructType", {
            StaticMethod("create", &StructType::create),
            StaticMethod("get", &StructType::get),
            InstanceMethod("setBody", &StructType::setBody),
            InstanceMethod("getPointerTo", &StructType::getPointerTo),
            InstanceMethod("isStructTy", &StructType::isStructTy),
            InstanceMethod("isIntegerTy", &StructType::isIntegerTy),
            InstanceMethod("isVoidTy", &StructType::isVoidTy),
            InstanceMethod("getTypeID", &StructType::getTypeID)
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
    if (value.IsNull()) {
        return nullptr;
    }
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
    unsigned argsLen = info.Length();
    if (!(argsLen == 2 && LLVMContext::IsClassOf(info[0]) && info[1].IsString()) &&
        !(argsLen >= 3 && LLVMContext::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsString())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::create);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    const std::string &name = info[argsLen == 2 ? 1 : 2].As<Napi::String>();
    llvm::StructType *structType;
    if (argsLen >= 3) {
        auto eleTypesArray = info[1].As<Napi::Array>();
        unsigned numElements = eleTypesArray.Length();
        std::vector<llvm::Type *> elementTypes(numElements);
        for (unsigned i = 0; i < numElements; ++i) {
            elementTypes[i] = Type::Extract(eleTypesArray.Get(i));
        }
        structType = llvm::StructType::create(context, elementTypes, name);
    } else {
        structType = llvm::StructType::create(context, name);
    }
    return StructType::New(env, structType);
}

Napi::Value StructType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (!(argsLen == 1 && LLVMContext::IsClassOf(info[0])) &&
        !(argsLen == 2 && LLVMContext::IsClassOf(info[0]) && info[1].IsArray())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::get);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    llvm::StructType *structType;
    if (argsLen == 2) {
        auto eleTypesArray = info[1].As<Napi::Array>();
        unsigned numElements = eleTypesArray.Length();
        std::vector<llvm::Type *> elementTypes(numElements);
        for (unsigned i = 0; i < numElements; ++i) {
            elementTypes[i] = Type::Extract(eleTypesArray.Get(i));
        }
        structType = llvm::StructType::get(context, elementTypes);
    } else {
        structType = llvm::StructType::get(context);
    }
    return StructType::New(env, structType);
}

void StructType::setBody(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsArray()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::StructType::setBody);
    }
    auto eleTypesArray = info[0].As<Napi::Array>();
    unsigned numElements = eleTypesArray.Length();
    std::vector<llvm::Type *> elementTypes(numElements);
    for (unsigned i = 0; i < numElements; ++i) {
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

Napi::Value StructType::isIntegerTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntegerType::isIntegerTy);
    }
    bool result = info.Length() == 0 ? structType->isIntegerTy() : structType->isIntegerTy(info[0].As<Napi::Number>());
    return Napi::Boolean::New(env, result);
}

Napi::Value StructType::isVoidTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), structType->isVoidTy());
}

Napi::Value StructType::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), structType->getTypeID());
}

//===----------------------------------------------------------------------===//
// class ArrayType
//===----------------------------------------------------------------------===//

void ArrayType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ArrayType", {
            StaticMethod("get", &ArrayType::get),
            StaticMethod("isValidElementType", &ArrayType::isValidElementType),
            InstanceMethod("getNumElements", &ArrayType::getNumElements),
            InstanceMethod("getElementType", &ArrayType::getElementType),
            InstanceMethod("isStructTy", &ArrayType::isStructTy),
            InstanceMethod("isVoidTy", &ArrayType::isVoidTy),
            InstanceMethod("getTypeID", &ArrayType::getTypeID)
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
    if (value.IsNull()) {
        return nullptr;
    }
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
    return Napi::Number::New(info.Env(), double(arrayType->getNumElements()));
}

Napi::Value ArrayType::getElementType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), arrayType->getElementType());
}

Napi::Value ArrayType::isStructTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), arrayType->isStructTy());
}

Napi::Value ArrayType::isVoidTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), arrayType->isVoidTy());
}

Napi::Value ArrayType::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), arrayType->getTypeID());
}

//===----------------------------------------------------------------------===//
// class PointerType
//===----------------------------------------------------------------------===//

void PointerType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PointerType", {
            StaticMethod("get", &PointerType::get),
            StaticMethod("getUnqual", &PointerType::getUnqual),
            InstanceMethod("getElementType", &PointerType::getElementType),
            InstanceMethod("isPointerTy", &PointerType::isPointerTy),
            InstanceMethod("isStructTy", &PointerType::isStructTy),
            InstanceMethod("isIntegerTy", &PointerType::isIntegerTy),
            InstanceMethod("isVoidTy", &PointerType::isVoidTy),
            InstanceMethod("getTypeID", &PointerType::getTypeID),
            InstanceMethod("getPointerElementType", &PointerType::getPointerElementType)
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
    if (value.IsNull()) {
        return nullptr;
    }
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

Napi::Value PointerType::getUnqual(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Type::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PointerType::getUnqual);
    }
    llvm::Type *type = Type::Extract(info[0]);
    llvm::PointerType *pointerType = llvm::PointerType::getUnqual(type);
    return PointerType::New(env, pointerType);
}

Napi::Value PointerType::getElementType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *elementType = pointerType->getElementType();
    return Type::New(env, elementType);
}

Napi::Value PointerType::isPointerTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), pointerType->isPointerTy());
}

llvm::PointerType *PointerType::getLLVMPrimitive() {
    return pointerType;
}

Napi::Value PointerType::isStructTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), pointerType->isStructTy());
}

Napi::Value PointerType::isIntegerTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IntegerType::isIntegerTy);
    }
    bool result = info.Length() == 0 ? pointerType->isIntegerTy() : pointerType->isIntegerTy(info[0].As<Napi::Number>());
    return Napi::Boolean::New(env, result);
}

Napi::Value PointerType::isVoidTy(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), pointerType->isVoidTy());
}

Napi::Value PointerType::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), pointerType->getTypeID());
}

Napi::Value PointerType::getPointerElementType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), pointerType->getPointerElementType());
}
