#pragma once

#include <napi.h>
#include <llvm/IR/IRBuilder.h>
#include "IR/index.h"
#include "Util/index.h"

#define getIntFactoryMacro(funcType) \
template<funcType method> \
Napi::Value getIntFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() == 1 && info[0].IsNumber()) { \
        unsigned value = info[0].As<Napi::Number>(); \
        return ConstantInt::New(env, (builder->*method)(value)); \
    } \
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntFactory); \
}

#define binOpFactoryMacro(binOpFuncType, ...) \
template<binOpFuncType method> \
Napi::Value binOpFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    unsigned argsLen = info.Length(); \
    if (argsLen == 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) || \
        argsLen == 3 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsString()) { \
        llvm::Value *lhs = Value::Extract(info[0]); \
        llvm::Value *rhs = Value::Extract(info[1]); \
        const std::string &name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : ""; \
        llvm::Value *result = (builder->*method)(lhs, rhs, name, ##__VA_ARGS__); \
        return Value::New(env, result); \
    } \
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateBinOpFactory); \
}

#define unOpFactoryMacro(unOpFuncType, ...) \
template<unOpFuncType method> \
Napi::Value unOpFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    unsigned argsLen = info.Length(); \
    if (argsLen == 1 && Value::IsClassOf(info[0]) || \
        argsLen == 2 && Value::IsClassOf(info[0]) && info[1].IsString()) { \
        llvm::Value *value = Value::Extract(info[0]); \
        const std::string &name = argsLen == 2 ? std::string(info[1].As<Napi::String>()) : ""; \
        llvm::Value *result = (builder->*method)(value, name, ##__VA_ARGS__); \
        return Value::New(env, result); \
    } \
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateUnOpFactory); \
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

    //===--------------------------------------------------------------------===//
    // Builder configuration methods
    //===--------------------------------------------------------------------===//

    void ClearInsertionPoint(const Napi::CallbackInfo &info);

    Napi::Value GetInsertBlock(const Napi::CallbackInfo &info);

    void SetInsertPoint(const Napi::CallbackInfo &info);

    void SetCurrentDebugLocation(const Napi::CallbackInfo &info);

    class InsertPoint : public Napi::ObjectWrap<InsertPoint> {
    public:
        static inline Napi::FunctionReference constructor; // NOLINT

        static Napi::Function Init(Napi::Env env, Napi::Object &exports);

        static Napi::Object New(Napi::Env env, llvm::IRBuilderBase::InsertPoint insertPoint);

        static bool IsClassOf(const Napi::Value &value);

        static llvm::IRBuilderBase::InsertPoint Extract(const Napi::Value &value);

        explicit InsertPoint(const Napi::CallbackInfo &info);

        llvm::IRBuilderBase::InsertPoint getLLVMPrimitive();

    private:
        static inline llvm::IRBuilderBase::InsertPoint tmpInsertPoint; // tmp in static-new

        llvm::IRBuilderBase::InsertPoint insertPoint;
    };

    Napi::Value saveIP(const Napi::CallbackInfo &info);

    Napi::Value saveAndClearIP(const Napi::CallbackInfo &info);

    void restoreIP(const Napi::CallbackInfo &info);

    //===--------------------------------------------------------------------===//
    // Miscellaneous creation methods.
    //===--------------------------------------------------------------------===//

    Napi::Value CreateGlobalString(const Napi::CallbackInfo &info);

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

    //===--------------------------------------------------------------------===//
    // Type creation methods
    //===--------------------------------------------------------------------===//

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

    //===--------------------------------------------------------------------===//
    // Instruction creation methods: Terminators
    //===--------------------------------------------------------------------===//

    Napi::Value CreateRetVoid(const Napi::CallbackInfo &info);

    Napi::Value CreateRet(const Napi::CallbackInfo &info);

    Napi::Value CreateBr(const Napi::CallbackInfo &info);

    Napi::Value CreateCondBr(const Napi::CallbackInfo &info);

    Napi::Value CreateSwitch(const Napi::CallbackInfo &info);

    Napi::Value CreateIndirectBr(const Napi::CallbackInfo &info);

    Napi::Value CreateInvoke(const Napi::CallbackInfo &info);

    Napi::Value CreateResume(const Napi::CallbackInfo &info);

    Napi::Value CreateUnreachable(const Napi::CallbackInfo &info);

    //===--------------------------------------------------------------------===//
    // Instruction creation methods: Binary Operators
    //===--------------------------------------------------------------------===//

    binOpFactoryMacro(BinaryOperation)

    binOpFactoryMacro(BinaryIntOperation, false, false)

    binOpFactoryMacro(BinaryFloatOperation, nullptr)

    binOpFactoryMacro(BinaryOperationWithBool, false)

    unOpFactoryMacro(UnaryOperation)

    unOpFactoryMacro(UnaryIntOperation, false, false)

    unOpFactoryMacro(UnaryFloatOperation, nullptr)

    //===--------------------------------------------------------------------===//
    // Instruction creation methods: Memory Instructions
    //===--------------------------------------------------------------------===//

    Napi::Value CreateAlloca(const Napi::CallbackInfo &info);

    Napi::Value CreateLoad(const Napi::CallbackInfo &info);

    Napi::Value CreateStore(const Napi::CallbackInfo &info);

    Napi::Value CreateGEP(const Napi::CallbackInfo &info);

    Napi::Value CreateInBoundsGEP(const Napi::CallbackInfo &info);

    Napi::Value CreateGlobalStringPtr(const Napi::CallbackInfo &info);

    //===--------------------------------------------------------------------===//
    // Instruction creation methods: Cast/Conversion Operators
    //===--------------------------------------------------------------------===//

    template<CreateCast method>
    Napi::Value CreateCastFactory(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        unsigned argsLen = info.Length();
        if (argsLen < 2 || !Value::IsClassOf(info[0]) || !Type::IsClassOf(info[1]) || argsLen >= 3 && !info[2].IsString()) {
            throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateCastFactory);
        }
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Type *destType = Type::Extract(info[1]);
        const std::string &name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        return Value::New(env, (builder->*method)(value, destType, name));
    }

    Napi::Value CreateIntCast(const Napi::CallbackInfo &info);

    //===--------------------------------------------------------------------===//
    // Instruction creation methods: Other Instructions
    //===--------------------------------------------------------------------===//

    Napi::Value CreatePHI(const Napi::CallbackInfo &info);

    Napi::Value CreateCall(const Napi::CallbackInfo &info);

    Napi::Value CreateSelect(const Napi::CallbackInfo &info);

    Napi::Value CreateExtractValue(const Napi::CallbackInfo &info);

    Napi::Value CreateInsertValue(const Napi::CallbackInfo &info);

    Napi::Value CreateLandingPad(const Napi::CallbackInfo &info);

    //===--------------------------------------------------------------------===//
    // Utility creation methods
    //===--------------------------------------------------------------------===//

    Napi::Value CreatePtrDiff(const Napi::CallbackInfo &info);
};
