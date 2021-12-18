#pragma once

#include <napi.h>
#include <llvm/IR/Constants.h>

class ConstantInt : public Napi::ObjectWrap<ConstantInt> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantInt *constantInt);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantInt *Extract(const Napi::Value &value);

    explicit ConstantInt(const Napi::CallbackInfo &info);

    llvm::ConstantInt *getLLVMPrimitive();

private:
    llvm::ConstantInt *constantInt = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};

class ConstantFP : public Napi::ObjectWrap<ConstantFP> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantFP *constantFP);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantFP *Extract(const Napi::Value &value);

    explicit ConstantFP(const Napi::CallbackInfo &info);

    llvm::ConstantFP *getLLVMPrimitive();

private:
    llvm::ConstantFP *constantFP = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    static Napi::Value getNaN(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};

class ConstantStruct : public Napi::ObjectWrap<ConstantStruct> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantStruct *constantStruct);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantStruct *Extract(const Napi::Value &value);

    explicit ConstantStruct(const Napi::CallbackInfo &info);

    llvm::ConstantStruct *getLLVMPrimitive();

private:
    llvm::ConstantStruct *constantStruct = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};

class ConstantPointerNull : public Napi::ObjectWrap<ConstantPointerNull> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantPointerNull *constantPointerNull);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantPointerNull *Extract(const Napi::Value &value);

    explicit ConstantPointerNull(const Napi::CallbackInfo &info);

    llvm::ConstantPointerNull *getLLVMPrimitive();

private:
    llvm::ConstantPointerNull *constantPointerNull = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};

class ConstantExpr : public Napi::ObjectWrap<ConstantExpr> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ConstantExpr *constantExpr);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ConstantExpr *Extract(const Napi::Value &value);

    explicit ConstantExpr(const Napi::CallbackInfo &info);

    llvm::ConstantExpr *getLLVMPrimitive();

private:
    llvm::ConstantExpr *constantExpr = nullptr;

    static Napi::Value getBitCast(const Napi::CallbackInfo &info);

    Napi::Value getType(const Napi::CallbackInfo &info);
};

class UndefValue : public Napi::ObjectWrap<UndefValue> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::UndefValue *undefValue);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::UndefValue *Extract(const Napi::Value &value);

    explicit UndefValue(const Napi::CallbackInfo &info);

    llvm::UndefValue *getLLVMPrimitive();

private:
    llvm::UndefValue *undefValue = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};
