#include "IR/index.h"
#include "Util/index.h"

typedef llvm::Type *(getTypeFn)(llvm::LLVMContext &);

typedef llvm::IntegerType *(getIntTypeFn)(llvm::LLVMContext &);

typedef llvm::PointerType *(getPointerTypeFn)(llvm::LLVMContext &, unsigned AS);


template<getTypeFn method>
Napi::Value getTypeFactory(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::getTypeFactory);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    llvm::Type *type = method(context);
    return Type::New(env, type);
}

template<getIntTypeFn method>
Napi::Value getIntTypeFactory(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::getIntTypeFactory);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    llvm::IntegerType *type = method(context);
    return IntegerType::New(env, type);
}

template<getPointerTypeFn method>
Napi::Value getPointerTypeFactory(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 0 || !LLVMContext::IsClassOf(info[0]) || argsLen >= 2 && !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::getPointerTypeFactory);
    }
    unsigned addrSpace = 0;
    if (info.Length() >= 2) {
        addrSpace = info[1].As<Napi::Number>();
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    llvm::PointerType *type = method(context, addrSpace);
    return PointerType::New(env, type);
}

void Type::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Object typeID = Napi::Object::New(env);
    typeID.Set("HalfTyID", Napi::Number::New(env, llvm::Type::TypeID::HalfTyID));
    typeID.Set("BFloatTyID", Napi::Number::New(env, llvm::Type::TypeID::BFloatTyID));
    typeID.Set("FloatTyID", Napi::Number::New(env, llvm::Type::TypeID::FloatTyID));
    typeID.Set("DoubleTyID", Napi::Number::New(env, llvm::Type::TypeID::DoubleTyID));
    typeID.Set("X86_FP80TyID", Napi::Number::New(env, llvm::Type::TypeID::X86_FP80TyID));
    typeID.Set("FP128TyID", Napi::Number::New(env, llvm::Type::TypeID::FP128TyID));
    typeID.Set("PPC_FP128TyID", Napi::Number::New(env, llvm::Type::TypeID::PPC_FP128TyID));
    typeID.Set("VoidTyID", Napi::Number::New(env, llvm::Type::TypeID::VoidTyID));
    typeID.Set("LabelTyID", Napi::Number::New(env, llvm::Type::TypeID::LabelTyID));
    typeID.Set("MetadataTyID", Napi::Number::New(env, llvm::Type::TypeID::MetadataTyID));
    typeID.Set("X86_MMXTyID", Napi::Number::New(env, llvm::Type::TypeID::X86_MMXTyID));
    typeID.Set("TokenTyID", Napi::Number::New(env, llvm::Type::TypeID::TokenTyID));
    typeID.Set("IntegerTyID", Napi::Number::New(env, llvm::Type::TypeID::IntegerTyID));
    typeID.Set("FunctionTyID", Napi::Number::New(env, llvm::Type::TypeID::FunctionTyID));
    typeID.Set("PointerTyID", Napi::Number::New(env, llvm::Type::TypeID::PointerTyID));
    typeID.Set("StructTyID", Napi::Number::New(env, llvm::Type::TypeID::StructTyID));
    typeID.Set("ArrayTyID", Napi::Number::New(env, llvm::Type::TypeID::ArrayTyID));
    typeID.Set("FixedVectorTyID", Napi::Number::New(env, llvm::Type::TypeID::FixedVectorTyID));
    typeID.Set("ScalableVectorTyID", Napi::Number::New(env, llvm::Type::TypeID::ScalableVectorTyID));

    Napi::Function func = DefineClass(env, "Type", {
            StaticValue("TypeID", typeID),
            StaticMethod("getVoidTy", &getTypeFactory<&llvm::Type::getVoidTy>),
            StaticMethod("getLabelTy", &getTypeFactory<&llvm::Type::getLabelTy>),
            StaticMethod("getHalfTy", &getTypeFactory<&llvm::Type::getHalfTy>),
            StaticMethod("getBFloatTy", &getTypeFactory<&llvm::Type::getBFloatTy>),
            StaticMethod("getFloatTy", &getTypeFactory<&llvm::Type::getFloatTy>),
            StaticMethod("getDoubleTy", &getTypeFactory<&llvm::Type::getDoubleTy>),
            StaticMethod("getMetadataTy", &getTypeFactory<&llvm::Type::getMetadataTy>),
            StaticMethod("getX86_FP80Ty", &getTypeFactory<&llvm::Type::getX86_FP80Ty>),
            StaticMethod("getFP128Ty", &getTypeFactory<&llvm::Type::getFP128Ty>),
            StaticMethod("getPPC_FP128Ty", &getTypeFactory<&llvm::Type::getPPC_FP128Ty>),
            StaticMethod("getX86_MMXTy", &getTypeFactory<&llvm::Type::getX86_MMXTy>),
            StaticMethod("getTokenTy", &getTypeFactory<&llvm::Type::getTokenTy>),
            StaticMethod("getIntNTy", &Type::getIntNTy),
            StaticMethod("getInt1Ty", &getIntTypeFactory<&llvm::Type::getInt1Ty>),
            StaticMethod("getInt8Ty", &getIntTypeFactory<&llvm::Type::getInt8Ty>),
            StaticMethod("getInt16Ty", &getIntTypeFactory<&llvm::Type::getInt16Ty>),
            StaticMethod("getInt32Ty", &getIntTypeFactory<&llvm::Type::getInt32Ty>),
            StaticMethod("getInt64Ty", &getIntTypeFactory<&llvm::Type::getInt64Ty>),
            StaticMethod("getInt128Ty", &getIntTypeFactory<&llvm::Type::getInt128Ty>),
            StaticMethod("getHalfPtrTy", &getPointerTypeFactory<&llvm::Type::getHalfPtrTy>),
            StaticMethod("getBFloatPtrTy", &getPointerTypeFactory<&llvm::Type::getBFloatPtrTy>),
            StaticMethod("getFloatPtrTy", &getPointerTypeFactory<&llvm::Type::getFloatPtrTy>),
            StaticMethod("getDoublePtrTy", &getPointerTypeFactory<&llvm::Type::getDoublePtrTy>),
            StaticMethod("getX86_FP80PtrTy", &getPointerTypeFactory<&llvm::Type::getX86_FP80PtrTy>),
            StaticMethod("getFP128PtrTy", &getPointerTypeFactory<&llvm::Type::getFP128PtrTy>),
            StaticMethod("getPPC_FP128PtrTy", &getPointerTypeFactory<&llvm::Type::getPPC_FP128PtrTy>),
            StaticMethod("getX86_MMXPtrTy", &getPointerTypeFactory<&llvm::Type::getX86_MMXPtrTy>),
            StaticMethod("getInt1PtrTy", &getPointerTypeFactory<&llvm::Type::getInt1PtrTy>),
            StaticMethod("getInt8PtrTy", &getPointerTypeFactory<&llvm::Type::getInt8PtrTy>),
            StaticMethod("getInt16PtrTy", &getPointerTypeFactory<&llvm::Type::getInt16PtrTy>),
            StaticMethod("getInt32PtrTy", &getPointerTypeFactory<&llvm::Type::getInt32PtrTy>),
            StaticMethod("getInt64PtrTy", &getPointerTypeFactory<&llvm::Type::getInt64PtrTy>),
            InstanceMethod("getTypeID", &Type::getTypeID),
            InstanceMethod("isVoidTy", &Type::isTypeFactory<&llvm::Type::isVoidTy>),
            InstanceMethod("isHalfTy", &Type::isTypeFactory<&llvm::Type::isHalfTy>),
            InstanceMethod("isBFloatTy", &Type::isTypeFactory<&llvm::Type::isBFloatTy>),
            InstanceMethod("isFloatTy", &Type::isTypeFactory<&llvm::Type::isFloatTy>),
            InstanceMethod("isDoubleTy", &Type::isTypeFactory<&llvm::Type::isDoubleTy>),
            InstanceMethod("isX86_FP80Ty", &Type::isTypeFactory<&llvm::Type::isX86_FP80Ty>),
            InstanceMethod("isFP128Ty", &Type::isTypeFactory<&llvm::Type::isFP128Ty>),
            InstanceMethod("isPPC_FP128Ty", &Type::isTypeFactory<&llvm::Type::isPPC_FP128Ty>),
            InstanceMethod("isFloatingPointTy", &Type::isTypeFactory<&llvm::Type::isFloatingPointTy>),
            InstanceMethod("isX86_MMXTy", &Type::isTypeFactory<&llvm::Type::isX86_MMXTy>),
            InstanceMethod("isLabelTy", &Type::isTypeFactory<&llvm::Type::isLabelTy>),
            InstanceMethod("isMetadataTy", &Type::isTypeFactory<&llvm::Type::isMetadataTy>),
            InstanceMethod("isTokenTy", &Type::isTypeFactory<&llvm::Type::isTokenTy>),
            InstanceMethod("isIntegerTy", &Type::isIntegerTy),
            InstanceMethod("isFunctionTy", &Type::isTypeFactory<&llvm::Type::isFunctionTy>),
            InstanceMethod("isStructTy", &Type::isTypeFactory<&llvm::Type::isStructTy>),
            InstanceMethod("isArrayTy", &Type::isTypeFactory<&llvm::Type::isArrayTy>),
            InstanceMethod("isPointerTy", &Type::isTypeFactory<&llvm::Type::isPointerTy>),
            InstanceMethod("isVectorTy", &Type::isTypeFactory<&llvm::Type::isVectorTy>),
            InstanceMethod("isEmptyTy", &Type::isTypeFactory<&llvm::Type::isEmptyTy>),
            InstanceMethod("isFirstClassType", &Type::isTypeFactory<&llvm::Type::isFirstClassType>),
            InstanceMethod("isSingleValueType", &Type::isTypeFactory<&llvm::Type::isSingleValueType>),
            InstanceMethod("isAggregateType", &Type::isTypeFactory<&llvm::Type::isAggregateType>),
            InstanceMethod("getPointerTo", &Type::getPointerTo),
            InstanceMethod("getPrimitiveSizeInBits", &Type::getPrimitiveSizeInBits),
            InstanceMethod("getPointerElementType", &Type::getPointerElementType),
            StaticMethod("isSameType", &Type::isSameType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Type", func);
}

Napi::Object Type::New(Napi::Env env, llvm::Type *type) {
    if (type->isIntegerTy()) {
        return IntegerType::New(env, llvm::cast<llvm::IntegerType>(type));
    } else if (type->isPointerTy()) {
        return PointerType::New(env, llvm::cast<llvm::PointerType>(type));
    } else if (type->isFunctionTy()) {
        return FunctionType::New(env, llvm::cast<llvm::FunctionType>(type));
    } else if (type->isArrayTy()) {
        return ArrayType::New(env, llvm::cast<llvm::ArrayType>(type));
    } else if (type->isStructTy()) {
        return StructType::New(env, llvm::cast<llvm::StructType>(type));
    }
    return constructor.New({Napi::External<llvm::Type>::New(env, type)});
}

bool Type::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Type *Type::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Type::Type(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Type>>();
    type = external.Data();
}

llvm::Type *Type::getLLVMPrimitive() {
    return type;
}

Napi::Value Type::getPointerTo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::getPointerTo);
    }
    unsigned addrSpace = 0;
    if (info.Length() >= 1) {
        addrSpace = info[0].As<Napi::Number>();
    }
    llvm::PointerType *pointerType = type->getPointerTo(addrSpace);
    return PointerType::New(env, pointerType);
}

Napi::Value Type::getTypeID(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), type->getTypeID());
}

Napi::Value Type::getIntNTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !LLVMContext::IsClassOf(info[0]) || !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::getIntNTy);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    unsigned n = info[1].As<Napi::Number>();
    llvm::IntegerType *type = llvm::Type::getIntNTy(context, n);
    return Type::New(env, type);
}

Napi::Value Type::getPrimitiveSizeInBits(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), double(type->getPrimitiveSizeInBits()));
}

Napi::Value Type::isIntegerTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Type::isIntegerTy);
    }
    bool result = info.Length() == 0 ? type->isIntegerTy() : type->isIntegerTy(info[0].As<Napi::Number>());
    return Napi::Boolean::New(env, result);
}

Napi::Value Type::getPointerElementType(const Napi::CallbackInfo &info) {
    return Type::New(info.Env(), type->getPointerElementType());
}

static bool isSameType(llvm::Type *type1, llvm::Type *type2) {
    if (type1 == nullptr || type2 == nullptr) {
        return type1 == type2;
    }
    if (type1->getTypeID() != type2->getTypeID()) {
        return false;
    }
    if (type1->isIntegerTy()) {
        return type1->getIntegerBitWidth() == type2->getIntegerBitWidth();
    } else if (type1->isFunctionTy()) {
        auto *funcType1 = llvm::cast<llvm::FunctionType>(type1);
        auto *funcType2 = llvm::cast<llvm::FunctionType>(type2);
        if (!isSameType(funcType1->getReturnType(), funcType2->getReturnType())) {
            return false;
        }
        unsigned numParams = funcType1->getNumParams();
        if (numParams != funcType2->getNumParams()) {
            return false;
        }
        for (unsigned i = 0; i < numParams; ++i) {
            if (!isSameType(funcType1->getParamType(i), funcType2->getParamType(i))) {
                return false;
            }
        }
    } else if (type1->isPointerTy()) {
        return isSameType(type1->getPointerElementType(), type2->getPointerElementType());
    } else if (type1->isStructTy()) {
        unsigned numElements = type1->getStructNumElements();
        if (numElements != type2->getStructNumElements()) {
            return false;
        }
        for (unsigned i = 0; i < numElements; ++i) {
            if (!isSameType(type1->getStructElementType(i), type2->getStructElementType(i))) {
                return false;
            }
        }
    } else if (type1->isArrayTy()) {
        return isSameType(type1->getArrayElementType(), type2->getArrayElementType());
    }
    // TODO: not support vector type
    return true;
}

Napi::Value Type::isSameType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Type::IsClassOf(info[0]) && Type::IsClassOf(info[1])) {
        llvm::Type *type1 = Type::Extract(info[0]);
        llvm::Type *type2 = Type::Extract(info[1]);
        return Napi::Boolean::New(env, ::isSameType(type1, type2));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Type::isSameType);
}
