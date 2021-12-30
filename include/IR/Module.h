#pragma once

#include <napi.h>
#include <llvm/IR/Module.h>

class Module : public Napi::ObjectWrap<Module> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::Module *module);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Module *Extract(const Napi::Value &value);

    explicit Module(const Napi::CallbackInfo &info);

    llvm::Module *getLLVMPrimitive();

private:
    llvm::Module *module = nullptr;

    Napi::Value getModuleIdentifier(const Napi::CallbackInfo &info);

    Napi::Value getSourceFileName(const Napi::CallbackInfo &info);

    Napi::Value getName(const Napi::CallbackInfo &info);

    Napi::Value getDataLayoutStr(const Napi::CallbackInfo &info);

    Napi::Value getDataLayout(const Napi::CallbackInfo &info);

    Napi::Value getTargetTriple(const Napi::CallbackInfo &info);

    void setModuleIdentifier(const Napi::CallbackInfo &info);

    void setSourceFileName(const Napi::CallbackInfo &info);

    void setDataLayout(const Napi::CallbackInfo &info);

    void setTargetTriple(const Napi::CallbackInfo &info);

    Napi::Value getFunction(const Napi::CallbackInfo &info);

    Napi::Value getOrInsertFunction(const Napi::CallbackInfo &info);

    Napi::Value getGlobalVariable(const Napi::CallbackInfo &info);

    void addModuleFlag(const Napi::CallbackInfo &info);

    Napi::Value empty(const Napi::CallbackInfo &info);

    Napi::Value print(const Napi::CallbackInfo &info);
};