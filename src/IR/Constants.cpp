#include "IR/index.h"
#include "ADT/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
// class Constant
//===----------------------------------------------------------------------===//

void Constant::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Constant", {
            StaticMethod("getNullValue", Constant::getNullValue),
            StaticMethod("getAllOnesValue", Constant::getAllOnesValue),
            InstanceMethod("isNullValue", &Constant::isNullValue),
            InstanceMethod("isOneValue", &Constant::isOneValue),
            InstanceMethod("isAllOnesValue", &Constant::isAllOnesValue),
            InstanceMethod("getType", &Constant::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), User::constructor.Value());
    exports.Set("Constant", func);
}

Napi::Object Constant::New(Napi::Env env, llvm::Constant *constant) {
    if (llvm::isa<llvm::GlobalValue>(constant)) {
        return GlobalValue::New(env, llvm::cast<llvm::GlobalValue>(constant));
    } else if (llvm::isa<llvm::ConstantInt>(constant)) {
        return ConstantInt::New(env, llvm::cast<llvm::ConstantInt>(constant));
    } else if (llvm::isa<llvm::ConstantFP>(constant)) {
        return ConstantFP::New(env, llvm::cast<llvm::ConstantFP>(constant));
    } else if (llvm::isa<llvm::ConstantExpr>(constant)) {
        return ConstantExpr::New(env, llvm::cast<llvm::ConstantExpr>(constant));
    } else if (llvm::isa<llvm::ConstantPointerNull>(constant)) {
        return ConstantPointerNull::New(env, llvm::cast<llvm::ConstantPointerNull>(constant));
    } else if (llvm::isa<llvm::ConstantStruct>(constant)) {
        return ConstantStruct::New(env, llvm::cast<llvm::ConstantStruct>(constant));
    }
    // TODO: more structured clearly
    return constructor.New({Napi::External<llvm::Constant>::New(env, constant)});
}

bool Constant::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Constant *Constant::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Constant::Constant(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Constant>>();
    constant = external.Data();
}

Napi::Value Constant::getNullValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Type::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::getNullValue);
    }
    llvm::Type *type = Type::Extract(info[0]);
    llvm::Constant *constant = llvm::Constant::getNullValue(type);
    return Constant::New(env, constant);
}

Napi::Value Constant::getAllOnesValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Type::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Constant::getAllOnesValue);
    }
    llvm::Type *type = Type::Extract(info[0]);
    llvm::Constant *constant = llvm::Constant::getAllOnesValue(type);
    return Constant::New(env, constant);
}

Napi::Value Constant::isNullValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isNullValue());
}

Napi::Value Constant::isOneValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isOneValue());
}

Napi::Value Constant::isAllOnesValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, constant->isAllOnesValue());
}

Napi::Value Constant::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = constant->getType();
    return Type::New(env, type);
}

llvm::Constant *Constant::getLLVMPrimitive() {
    return constant;
}

//===----------------------------------------------------------------------===//
// class ConstantInt
//===----------------------------------------------------------------------===//

typedef llvm::ConstantInt *(GetBool)(llvm::LLVMContext &);

template<GetBool method>
Napi::Value getBoolFactory(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "ConstantInt.getTrue/getFalse needs to be called with: (context: LLVMContext)");
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    llvm::ConstantInt *constantInt = method(context);
    return ConstantInt::New(env, constantInt);
}

void ConstantInt::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantInt", {
            StaticMethod("get", &ConstantInt::get),
            StaticMethod("getTrue", &getBoolFactory<llvm::ConstantInt::getTrue>),
            StaticMethod("getFalse", &getBoolFactory<llvm::ConstantInt::getFalse>),
            InstanceMethod("getType", &ConstantInt::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantInt", func);
}

Napi::Object ConstantInt::New(Napi::Env env, llvm::ConstantInt *constantInt) {
    return constructor.New({Napi::External<llvm::ConstantInt>::New(env, constantInt)});
}

bool ConstantInt::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantInt *ConstantInt::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantInt::ConstantInt(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantInt::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantInt>>();
    constantInt = external.Data();
}

llvm::ConstantInt *ConstantInt::getLLVMPrimitive() {
    return constantInt;
}

Napi::Value ConstantInt::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen >= 2 && LLVMContext::IsClassOf(info[0]) && APInt::IsClassOf(info[1])) {
        llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
        llvm::APInt &value = APInt::Extract(info[1]);
        return ConstantInt::New(env, llvm::ConstantInt::get(context, value));
    } else if (argsLen >= 2 && IntegerType::IsClassOf(info[0]) && info[1].IsNumber()) {
        llvm::IntegerType *intType = IntegerType::Extract(info[0]);
        uint64_t value = info[1].As<Napi::Number>().Int64Value();
        bool isSigned = argsLen >= 3 && info[2].As<Napi::Boolean>();
        return ConstantInt::New(env, llvm::ConstantInt::get(intType, value, isSigned));
    } else if (argsLen >= 2 && Type::IsClassOf(info[0])) {
        llvm::Type *type = Type::Extract(info[0]);
        if (APInt::IsClassOf(info[1])) {
            llvm::APInt &value = APInt::Extract(info[1]);
            return Constant::New(env, llvm::ConstantInt::get(type, value));
        } else if (info[1].IsNumber()) {
            uint64_t value = info[1].As<Napi::Number>().Int64Value();
            bool isSigned = argsLen >= 3 && info[2].As<Napi::Boolean>();
            return Constant::New(env, llvm::ConstantInt::get(type, value, isSigned));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::ConstantInt::get);
}

Napi::Value ConstantInt::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::IntegerType *type = constantInt->getType();
    return IntegerType::New(env, type);
}

//===----------------------------------------------------------------------===//
// class ConstantFP
//===----------------------------------------------------------------------===//

void ConstantFP::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantFP", {
            StaticMethod("get", &ConstantFP::get),
            StaticMethod("getNaN", &ConstantFP::getNaN),
            InstanceMethod("getType", &ConstantFP::getType)
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
    if (value.IsNull()) {
        return nullptr;
    }
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

Napi::Value ConstantFP::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = constantFP->getType();
    return Type::New(env, type);
}

//===----------------------------------------------------------------------===//
// class ConstantStruct
//===----------------------------------------------------------------------===//

void ConstantStruct::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantStruct", {
            StaticMethod("get", &ConstantStruct::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantStruct", func);
}

Napi::Object ConstantStruct::New(Napi::Env env, llvm::ConstantStruct *constantStruct) {
    return constructor.New({Napi::External<llvm::ConstantStruct>::New(env, constantStruct)});
}

bool ConstantStruct::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantStruct *ConstantStruct::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantStruct::ConstantStruct(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantStruct::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantStruct>>();
    constantStruct = external.Data();
}

llvm::ConstantStruct *ConstantStruct::getLLVMPrimitive() {
    return constantStruct;
}

Napi::Value ConstantStruct::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !StructType::IsClassOf(info[0]) || !info[1].IsArray()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantStruct::get);
    }
    llvm::StructType *structType = StructType::Extract(info[0]);
    auto valuesArray = info[1].As<Napi::Array>();
    unsigned numValues = valuesArray.Length();
    std::vector<llvm::Constant *> values(numValues);
    for (unsigned i = 0; i < numValues; ++i) {
        values[i] = Constant::Extract(valuesArray.Get(i));
    }
    llvm::Constant *constantStruct = llvm::ConstantStruct::get(structType, values);
    return Constant::New(env, constantStruct);
}

//===----------------------------------------------------------------------===//
// class ConstantPointerNull
//===----------------------------------------------------------------------===//

void ConstantPointerNull::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantPointerNull", {
            StaticMethod("get", &ConstantPointerNull::get),
            InstanceMethod("getType", &ConstantPointerNull::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantPointerNull", func);
}

Napi::Object ConstantPointerNull::New(Napi::Env env, llvm::ConstantPointerNull *constantPointerNull) {
    return constructor.New({Napi::External<llvm::ConstantPointerNull>::New(env, constantPointerNull)});
}

bool ConstantPointerNull::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantPointerNull *ConstantPointerNull::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantPointerNull::ConstantPointerNull(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantPointerNull::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantPointerNull>>();
    constantPointerNull = external.Data();
}

llvm::ConstantPointerNull *ConstantPointerNull::getLLVMPrimitive() {
    return constantPointerNull;
}

Napi::Value ConstantPointerNull::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !PointerType::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantPointerNull::get);
    }
    llvm::PointerType *type = PointerType::Extract(info[0]);
    return ConstantPointerNull::New(env, llvm::ConstantPointerNull::get(type));
}

Napi::Value ConstantPointerNull::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::PointerType *type = constantPointerNull->getType();
    return PointerType::New(env, type);
}

//===----------------------------------------------------------------------===//
// class ConstantExpr
//===----------------------------------------------------------------------===//

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
    if (value.IsNull()) {
        return nullptr;
    }
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

//===----------------------------------------------------------------------===//
// class UndefValue
//===----------------------------------------------------------------------===//

void UndefValue::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "UndefValue", {
            StaticMethod("get", &UndefValue::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("UndefValue", func);
}

Napi::Object UndefValue::New(Napi::Env env, llvm::UndefValue *undefValue) {
    return constructor.New({Napi::External<llvm::UndefValue>::New(env, undefValue)});
}

bool UndefValue::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::UndefValue *UndefValue::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

UndefValue::UndefValue(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::UndefValue::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::UndefValue >>();
    undefValue = external.Data();
}

llvm::UndefValue *UndefValue::getLLVMPrimitive() {
    return undefValue;
}

Napi::Value UndefValue::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && Type::IsClassOf(info[0])) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::UndefValue *undefValue = llvm::UndefValue::get(type);
        return UndefValue::New(env, undefValue);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::UndefValue::get);
}
