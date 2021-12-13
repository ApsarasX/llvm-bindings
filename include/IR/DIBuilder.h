#pragma once

#include <napi.h>
#include <llvm/IR/DIBuilder.h>

class DIBuilder : public Napi::ObjectWrap<DIBuilder> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIBuilder *builder);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIBuilder *Extract(const Napi::Value &value);

    explicit DIBuilder(const Napi::CallbackInfo &info);

    llvm::DIBuilder *getLLVMPrimitive();

private:
    llvm::DIBuilder *builder = nullptr;

    Napi::Value createFile(const Napi::CallbackInfo &info);

    Napi::Value createCompileUnit(const Napi::CallbackInfo &info);

    Napi::Value createFunction(const Napi::CallbackInfo &info);

    Napi::Value createBasicType(const Napi::CallbackInfo &info);

    Napi::Value getOrCreateTypeArray(const Napi::CallbackInfo &info);

    Napi::Value createSubroutineType(const Napi::CallbackInfo &info);

    Napi::Value createExpression(const Napi::CallbackInfo &info);

    Napi::Value createParameterVariable(const Napi::CallbackInfo &info);

    Napi::Value createAutoVariable(const Napi::CallbackInfo &info);

    Napi::Value createGlobalVariableExpression(const Napi::CallbackInfo &info);

    Napi::Value insertDeclare(const Napi::CallbackInfo &info);

    Napi::Value insertDbgValueIntrinsic(const Napi::CallbackInfo &info);

    void finalizeSubprogram(const Napi::CallbackInfo &info);

    void finalize(const Napi::CallbackInfo &info);
};