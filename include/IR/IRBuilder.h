#pragma once

#include <napi.h>
#include <llvm/IR/IRBuilder.h>

#include "IR/IR.h"
#include "Util/Util.h"

#define unOpFactoryMacro(unOpFuncType, extraArgs...) \
template<unOpFuncType method> \
Napi::Value unOpFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    size_t argsLen = info.Length(); \
    if(argsLen >= 1 && Value::IsClassOf(info[0])) { \
        if(argsLen == 1 || argsLen >= 2 && info[1].IsString()) { \
            llvm::Value *value = Value::Extract(info[0]); \
            const std::string &name = argsLen >= 2 ? info[1].As<Napi::String>().Utf8Value() : ""; \
            llvm::Value *result = (builder->*method)(value, name, ##extraArgs); \
            return Value::New(env, result); \
        } \
    } \
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateUnOpFactory); \
}

#define binOpFactoryMacro(binOpFuncType, extraArgs...) \
template<binOpFuncType method> \
Napi::Value binOpFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    size_t argsLen = info.Length(); \
    if(argsLen >= 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1])) { \
        if(argsLen == 2 || argsLen >= 3 && info[2].IsString()) { \
            llvm::Value *lhs = Value::Extract(info[0]); \
            llvm::Value *rhs = Value::Extract(info[1]); \
            const std::string &name = argsLen >= 3 ? info[2].As<Napi::String>().Utf8Value() : ""; \
            llvm::Value *result = (builder->*method)(lhs, rhs, name, ##extraArgs); \
            return Value::New(env, result); \
        } \
    } \
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateBinOpFactory); \
}

#define getIntFactoryMacro(funcType) \
template<funcType method> \
Napi::Value getIntFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() == 0 || !info[0].IsNumber()) { \
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntFactory); \
    } \
    unsigned value = info[0].As<Napi::Number>(); \
    return ConstantInt::New(env, (builder->*method)(value)); \
}

typedef llvm::IRBuilder<> LLVMIRBuilder;

typedef llvm::Value *(llvm::IRBuilderBase::*UnaryOperation)(llvm::Value *, const llvm::Twine &);

typedef llvm::Value *(llvm::IRBuilderBase::*UnaryIntOperation)(llvm::Value *, const llvm::Twine &, bool HasNUW, bool HasNSW);

typedef llvm::Value *(llvm::IRBuilderBase::*UnaryFloatOperation)(llvm::Value *, const llvm::Twine &, llvm::MDNode *FPMathTag);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryIntOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &, bool HasNUW, bool HasNSW);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryFloatOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &, llvm::MDNode *FPMathTag);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryOperationWithBool)(llvm::Value *, llvm::Value *, const llvm::Twine &, bool isExact);

typedef llvm::ConstantInt *(llvm::IRBuilderBase::*GetBoolean)();

typedef llvm::ConstantInt *(llvm::IRBuilderBase::*GetInt8)(uint8_t);

typedef llvm::ConstantInt *(llvm::IRBuilderBase::*GetInt16)(uint16_t);

typedef llvm::ConstantInt *(llvm::IRBuilderBase::*GetInt32)(uint32_t);

typedef llvm::ConstantInt *(llvm::IRBuilderBase::*GetInt64)(uint64_t);

typedef llvm::IntegerType *(llvm::IRBuilderBase::*GetIntType)();

typedef llvm::Type *(llvm::IRBuilderBase::*GetType)();

typedef llvm::Value *(llvm::IRBuilderBase::*CreateCast)(llvm::Value *, llvm::Type *, const llvm::Twine &name);

class IRBuilder : public Napi::ObjectWrap<IRBuilder> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static LLVMIRBuilder *Extract(const Napi::Value &value);

    explicit IRBuilder(const Napi::CallbackInfo &info);

    LLVMIRBuilder *getLLVMPrimitive();

private:
    LLVMIRBuilder *builder = nullptr;

    void setInsertionPoint(const Napi::CallbackInfo &info);

    Napi::Value createAlloca(const Napi::CallbackInfo &info);

    Napi::Value createBr(const Napi::CallbackInfo &info);

    Napi::Value createCall(const Napi::CallbackInfo &info);

    Napi::Value createCondBr(const Napi::CallbackInfo &info);

    Napi::Value createUnreachable(const Napi::CallbackInfo &info);

    Napi::Value createLoad(const Napi::CallbackInfo &info);

    Napi::Value createRet(const Napi::CallbackInfo &info);

    Napi::Value createRetVoid(const Napi::CallbackInfo &info);

    Napi::Value createSwitch(const Napi::CallbackInfo &info);

    Napi::Value createStore(const Napi::CallbackInfo &info);

    unOpFactoryMacro(UnaryOperation)

    unOpFactoryMacro(UnaryIntOperation, false, false)

    unOpFactoryMacro(UnaryFloatOperation, nullptr)

    binOpFactoryMacro(BinaryOperation)

    binOpFactoryMacro(BinaryIntOperation, false, false)

    binOpFactoryMacro(BinaryFloatOperation, nullptr)

    binOpFactoryMacro(BinaryOperationWithBool, false)

    Napi::Value createGlobalString(const Napi::CallbackInfo &info);

    Napi::Value createGlobalStringPtr(const Napi::CallbackInfo &info);

    Napi::Value createPHI(const Napi::CallbackInfo &info);

    template<CreateCast method>
    Napi::Value createCastFactory(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        int argsLen = info.Length();
        if (argsLen < 2 || !Value::IsClassOf(info[0]) || !Type::IsClassOf(info[1]) || argsLen >= 3 && !info[2].IsString()) {
            throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateCastFactory);
        }
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Type *destType = Type::Extract(info[1]);
        const std::string &name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        return Value::New(env, (builder->*method)(value, destType, name));
    }

    Napi::Value createIntCast(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        int argsLen = info.Length();
        if (argsLen < 3 ||
            !Value::IsClassOf(info[0]) ||
            !Type::IsClassOf(info[1]) ||
            !info[2].IsBoolean() ||
            argsLen >= 4 && !info[2].IsString()) {
            throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateIntCast);
        }
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Type *destType = Type::Extract(info[1]);
        bool isSigned = info[2].As<Napi::Boolean>();
        const std::string &name = argsLen >= 4 ? std::string(info[3].As<Napi::String>()) : "";
        return Value::New(env, builder->CreateIntCast(value, destType, isSigned, name));
    }

    Napi::Value createGEP(const Napi::CallbackInfo &info);

    Napi::Value createInBoundsGEP(const Napi::CallbackInfo &info);

    Napi::Value createSelect(const Napi::CallbackInfo &info);

    Napi::Value getInt1(const Napi::CallbackInfo &info);

    template<GetBoolean method>
    Napi::Value getBoolFactory(const Napi::CallbackInfo &info) {
        return ConstantInt::New(info.Env(), (builder->*method)());
    }

    getIntFactoryMacro(GetInt8)

    getIntFactoryMacro(GetInt16)

    getIntFactoryMacro(GetInt32)

    getIntFactoryMacro(GetInt64)

    Napi::Value getIntN(const Napi::CallbackInfo &info);

    Napi::Value getInt(const Napi::CallbackInfo &info);

    template<GetIntType method>
    Napi::Value getIntTypeFactory(const Napi::CallbackInfo &info) {
        return IntegerType::New(info.Env(), (builder->*method)());
    }

    template<GetType method>
    Napi::Value getTypeFactory(const Napi::CallbackInfo &info) {
        return Type::New(info.Env(), (builder->*method)());
    }

    Napi::Value getIntNTy(const Napi::CallbackInfo &info);

    Napi::Value getInt8PtrTy(const Napi::CallbackInfo &info);

    Napi::Value getIntPtrTy(const Napi::CallbackInfo &info);

    Napi::Value GetInsertBlock(const Napi::CallbackInfo &info);

    void ClearInsertionPoint(const Napi::CallbackInfo &info);
};