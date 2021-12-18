#pragma once

#include <napi.h>
#include <llvm/IR/DerivedTypes.h>

class IntegerType : public Napi::ObjectWrap<IntegerType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::IntegerType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::IntegerType *Extract(const Napi::Value &value);

    explicit IntegerType(const Napi::CallbackInfo &info);

    llvm::IntegerType *getLLVMPrimitive();

private:
    llvm::IntegerType *integerType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);
};

class FunctionType : public Napi::ObjectWrap<FunctionType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FunctionType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionType *Extract(const Napi::Value &value);

    explicit FunctionType(const Napi::CallbackInfo &info);

    llvm::FunctionType *getLLVMPrimitive();

private:
    llvm::FunctionType *functionType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);
};

class FunctionCallee : public Napi::ObjectWrap<FunctionCallee> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FunctionCallee callee);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionCallee Extract(const Napi::Value &value);

    explicit FunctionCallee(const Napi::CallbackInfo &info);

    llvm::FunctionCallee getLLVMPrimitive();

private:
    static inline llvm::FunctionCallee tmpCallee; // tmp in static-new

    llvm::FunctionCallee callee;

    Napi::Value getFunctionType(const Napi::CallbackInfo &info);

    Napi::Value getCallee(const Napi::CallbackInfo &info);
};

class StructType : public Napi::ObjectWrap<StructType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::StructType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::StructType *Extract(const Napi::Value &value);

    explicit StructType(const Napi::CallbackInfo &info);

    llvm::StructType *getLLVMPrimitive();

private:
    llvm::StructType *structType = nullptr;

    static Napi::Value create(const Napi::CallbackInfo &info);

    static Napi::Value get(const Napi::CallbackInfo &info);

    void setBody(const Napi::CallbackInfo &info);

    Napi::Value getPointerTo(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);
};

class ArrayType : public Napi::ObjectWrap<ArrayType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::ArrayType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ArrayType *Extract(const Napi::Value &value);

    explicit ArrayType(const Napi::CallbackInfo &info);

    llvm::ArrayType *getLLVMPrimitive();

private:
    llvm::ArrayType *arrayType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    static Napi::Value isValidElementType(const Napi::CallbackInfo &info);

    Napi::Value getNumElements(const Napi::CallbackInfo &info);

    Napi::Value getElementType(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);
};

class PointerType : public Napi::ObjectWrap<PointerType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::PointerType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::PointerType *Extract(const Napi::Value &value);

    explicit PointerType(const Napi::CallbackInfo &info);

    llvm::PointerType *getLLVMPrimitive();

private:
    llvm::PointerType *pointerType = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);

    static Napi::Value getUnqual(const Napi::CallbackInfo &info);

    Napi::Value getElementType(const Napi::CallbackInfo &info);

    Napi::Value isPointerTy(const Napi::CallbackInfo &info);

    Napi::Value isStructTy(const Napi::CallbackInfo &info);

    Napi::Value isIntegerTy(const Napi::CallbackInfo &info);

    Napi::Value isVoidTy(const Napi::CallbackInfo &info);

    Napi::Value getTypeID(const Napi::CallbackInfo &info);

    Napi::Value getPointerElementType(const Napi::CallbackInfo &info);
};
