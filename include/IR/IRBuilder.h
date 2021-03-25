#pragma once

#include <napi.h>
#include <llvm/IR/IRBuilder.h>
#include "IR/Value.h"

#define binOpFactoryMacro(binOpFuncType, extraArgs...) \
template<binOpFuncType method> \
Napi::Value binOpFactory(const Napi::CallbackInfo &info) { \
    Napi::Env env = info.Env(); \
    size_t argsLen = info.Length(); \
    bool flag = argsLen >= 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]); \
    if (argsLen >= 3 && flag && info[2].IsString() || argsLen == 2 && flag) { \
        llvm::Value *lhs = Value::Extract(info[0]); \
        llvm::Value *rhs = Value::Extract(info[1]); \
        const std::string &name = argsLen >= 3 ? info[2].As<Napi::String>().Utf8Value() : ""; \
        llvm::Value *result = (builder->*method)( lhs, rhs, name, ##extraArgs); \
        return Value::New(env, result); \
    } \
    throw Napi::TypeError::New(env, "IRBuilder createBinaryOperation needs to be called with: (lhs: Value, rhs: Value, name?: string)"); \
} \

typedef llvm::IRBuilder<> LLVMIRBuilder;

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryIntOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &, bool HasNUW, bool HasNSW);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryFloatOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &, llvm::MDNode *FPMathTag);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryOperation)(llvm::Value *, llvm::Value *, const llvm::Twine &);

typedef llvm::Value *(llvm::IRBuilderBase::*BinaryOperationWithBool)(llvm::Value *, llvm::Value *, const llvm::Twine &, bool isExact);


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

    Napi::Value createLoad(const Napi::CallbackInfo &info);

    Napi::Value createRet(const Napi::CallbackInfo &info);

    Napi::Value createRetVoid(const Napi::CallbackInfo &info);

    Napi::Value createStore(const Napi::CallbackInfo &info);

    binOpFactoryMacro(BinaryIntOperation, false, false)

    binOpFactoryMacro(BinaryFloatOperation, nullptr)

    binOpFactoryMacro(BinaryOperation)

    binOpFactoryMacro(BinaryOperationWithBool, false)
};