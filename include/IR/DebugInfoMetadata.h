#pragma once

#include <napi.h>
#include <llvm/IR/DebugInfoMetadata.h>

class DITypeRefArray : public Napi::ObjectWrap<DITypeRefArray> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DITypeRefArray *array);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DITypeRefArray *Extract(const Napi::Value &value);

    explicit DITypeRefArray(const Napi::CallbackInfo &info);

    llvm::DITypeRefArray *getLLVMPrimitive();

private:
    llvm::DITypeRefArray *array = nullptr;
};

class DINode : public Napi::ObjectWrap<DINode> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DINode *node);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DINode *Extract(const Napi::Value &value);

    explicit DINode(const Napi::CallbackInfo &info);

    llvm::DINode *getLLVMPrimitive();

private:
    llvm::DINode *node = nullptr;
};

class DIScope : public Napi::ObjectWrap<DIScope> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIScope *scope);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIScope *Extract(const Napi::Value &value);

    explicit DIScope(const Napi::CallbackInfo &info);

    llvm::DIScope *getLLVMPrimitive();

private:
    llvm::DIScope *scope = nullptr;
};

class DIFile : public Napi::ObjectWrap<DIFile> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIFile *file);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIFile *Extract(const Napi::Value &value);

    explicit DIFile(const Napi::CallbackInfo &info);

    llvm::DIFile *getLLVMPrimitive();

private:
    llvm::DIFile *file = nullptr;
};

class DIType : public Napi::ObjectWrap<DIType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIType *Extract(const Napi::Value &value);

    explicit DIType(const Napi::CallbackInfo &info);

    llvm::DIType *getLLVMPrimitive();

private:
    llvm::DIType *type = nullptr;
};

class DIBasicType : public Napi::ObjectWrap<DIBasicType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIBasicType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIBasicType *Extract(const Napi::Value &value);

    explicit DIBasicType(const Napi::CallbackInfo &info);

    llvm::DIBasicType *getLLVMPrimitive();

private:
    llvm::DIBasicType *type = nullptr;
};

class DISubroutineType : public Napi::ObjectWrap<DISubroutineType> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DISubroutineType *type);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DISubroutineType *Extract(const Napi::Value &value);

    explicit DISubroutineType(const Napi::CallbackInfo &info);

    llvm::DISubroutineType *getLLVMPrimitive();

private:
    llvm::DISubroutineType *type = nullptr;
};

class DICompileUnit : public Napi::ObjectWrap<DICompileUnit> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DICompileUnit *unit);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DICompileUnit *Extract(const Napi::Value &value);

    explicit DICompileUnit(const Napi::CallbackInfo &info);

    llvm::DICompileUnit *getLLVMPrimitive();

private:
    llvm::DICompileUnit *unit = nullptr;

    Napi::Value getFile(const Napi::CallbackInfo &info);
};

class DILocalScope : public Napi::ObjectWrap<DILocalScope> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocalScope *scope);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocalScope *Extract(const Napi::Value &value);

    explicit DILocalScope(const Napi::CallbackInfo &info);

    llvm::DILocalScope *getLLVMPrimitive();

private:
    llvm::DILocalScope *scope = nullptr;
};

class DILocation : public Napi::ObjectWrap<DILocation> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocation *location);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocation *Extract(const Napi::Value &value);

    explicit DILocation(const Napi::CallbackInfo &info);

    llvm::DILocation *getLLVMPrimitive();

private:
    llvm::DILocation *location = nullptr;

    static Napi::Value get(const Napi::CallbackInfo &info);
};

class DISubprogram : public Napi::ObjectWrap<DISubprogram> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DISubprogram *subProgram);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DISubprogram *Extract(const Napi::Value &value);

    explicit DISubprogram(const Napi::CallbackInfo &info);

    llvm::DISubprogram *getLLVMPrimitive();

private:
    llvm::DISubprogram *subprogram = nullptr;
};

class DILexicalBlock : public Napi::ObjectWrap<DILexicalBlock> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILexicalBlock *block);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILexicalBlock *Extract(const Napi::Value &value);

    explicit DILexicalBlock(const Napi::CallbackInfo &info);

    llvm::DILexicalBlock *getLLVMPrimitive();

private:
    llvm::DILexicalBlock *block = nullptr;
};

class DIVariable : public Napi::ObjectWrap<DIVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIVariable *Extract(const Napi::Value &value);

    explicit DIVariable(const Napi::CallbackInfo &info);

    llvm::DIVariable *getLLVMPrimitive();

private:
    llvm::DIVariable *variable = nullptr;
};

class DIExpression : public Napi::ObjectWrap<DIExpression> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIExpression *expression);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIExpression *Extract(const Napi::Value &value);

    explicit DIExpression(const Napi::CallbackInfo &info);

    llvm::DIExpression *getLLVMPrimitive();

private:
    llvm::DIExpression *expression = nullptr;
};

class DIGlobalVariable : public Napi::ObjectWrap<DIGlobalVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIGlobalVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIGlobalVariable *Extract(const Napi::Value &value);

    explicit DIGlobalVariable(const Napi::CallbackInfo &info);

    llvm::DIGlobalVariable *getLLVMPrimitive();

private:
    llvm::DIGlobalVariable *variable = nullptr;
};

class DILocalVariable : public Napi::ObjectWrap<DILocalVariable> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DILocalVariable *variable);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DILocalVariable *Extract(const Napi::Value &value);

    explicit DILocalVariable(const Napi::CallbackInfo &info);

    llvm::DILocalVariable *getLLVMPrimitive();

private:
    llvm::DILocalVariable *variable = nullptr;
};

class DIGlobalVariableExpression : public Napi::ObjectWrap<DIGlobalVariableExpression> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::DIGlobalVariableExpression *expression);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::DIGlobalVariableExpression *Extract(const Napi::Value &value);

    explicit DIGlobalVariableExpression(const Napi::CallbackInfo &info);

    llvm::DIGlobalVariableExpression *getLLVMPrimitive();

private:
    llvm::DIGlobalVariableExpression *expression = nullptr;
};
