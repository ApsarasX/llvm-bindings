#pragma once

#include <napi.h>

#include <llvm/IR/PassManager.h>
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"

class ModulePassManager : public Napi::ObjectWrap<ModulePassManager> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::ModulePassManager *Extract(const Napi::Value &value);

    explicit ModulePassManager(const Napi::CallbackInfo &info);

    llvm::ModulePassManager *getLLVMPrimitive();

private:
    llvm::ModulePassManager *passManager;

    llvm::PassBuilder *passBuilder;
    llvm::ModuleAnalysisManager *moduleAnalysisManager;
    llvm::LoopAnalysisManager *loopAnalysisManager;
    llvm::FunctionAnalysisManager *functionAnalysisManager;
    llvm::CGSCCAnalysisManager *cgsccAnalysisManager;

    llvm::OptimizationLevel level;

    Napi::Value createFunctionPassManager(const Napi::CallbackInfo &info);
    void addFunctionPasses(const Napi::CallbackInfo &info);
    void addVerifierPass(const Napi::CallbackInfo &info);
    Napi::Value isEmpty(const Napi::CallbackInfo &info);

    void run(const Napi::CallbackInfo &info);
};

class FunctionPassManager : public Napi::ObjectWrap<FunctionPassManager> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Object New(Napi::Env env, llvm::FunctionPassManager *fpm);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::FunctionPassManager *Extract(const Napi::Value &value);

    explicit FunctionPassManager(const Napi::CallbackInfo &info);

    llvm::FunctionPassManager *getLLVMPrimitive();

private:
    llvm::FunctionPassManager *passManager = nullptr;

    void addSROAPass(const Napi::CallbackInfo &info);
    void addEarlyCSEPass(const Napi::CallbackInfo &info);
    void addInstCombinePass(const Napi::CallbackInfo &info);

    Napi::Value isEmpty(const Napi::CallbackInfo &info);
};
