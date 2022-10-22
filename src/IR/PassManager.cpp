#include "IR/index.h"
#include "Util/index.h"

#include "Passes/OptimizationLevel.h"

#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/Scalar/SROA.h"
#include "llvm/Transforms/Scalar/EarlyCSE.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"

//===----------------------------------------------------------------------===//
//                        ModulePassManager Class
//===----------------------------------------------------------------------===//

void ModulePassManager::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ModulePassManager", {
            InstanceMethod("createFunctionPassManager", &ModulePassManager::createFunctionPassManager),
            InstanceMethod("addFunctionPasses", &ModulePassManager::addFunctionPasses),
            InstanceMethod("addVerifierPass", &ModulePassManager::addVerifierPass),
            InstanceMethod("isEmpty", &ModulePassManager::isEmpty),
            InstanceMethod("run", &ModulePassManager::run),
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), GlobalObject::constructor.Value());
    exports.Set("ModulePassManager", func);
}

bool ModulePassManager::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ModulePassManager *ModulePassManager::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

llvm::OptimizationLevel mapToLLVM(OptimizationLevel::Level opt) {
    switch (opt) {
        case OptimizationLevel::O1: return llvm::OptimizationLevel::O1;
        case OptimizationLevel::O2: return llvm::OptimizationLevel::O2;
        case OptimizationLevel::O3: return llvm::OptimizationLevel::O3;
        case OptimizationLevel::Os: return llvm::OptimizationLevel::Os;
        case OptimizationLevel::Oz: return llvm::OptimizationLevel::Oz;
        default: return llvm::OptimizationLevel::O0;
    }
}

ModulePassManager::ModulePassManager(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    level = mapToLLVM((OptimizationLevel::Level) info[0].As<Napi::Number>().Uint32Value());

    passBuilder = new llvm::PassBuilder();

    moduleAnalysisManager = new llvm::ModuleAnalysisManager();
    cgsccAnalysisManager = new llvm::CGSCCAnalysisManager();
    functionAnalysisManager = new llvm::FunctionAnalysisManager();
    loopAnalysisManager = new llvm::LoopAnalysisManager ();

    passBuilder->registerModuleAnalyses(*moduleAnalysisManager);
    passBuilder->registerCGSCCAnalyses(*cgsccAnalysisManager);
    passBuilder->registerFunctionAnalyses(*functionAnalysisManager);
    passBuilder->registerLoopAnalyses(*loopAnalysisManager);
    passBuilder->crossRegisterProxies(
        *loopAnalysisManager,
        *functionAnalysisManager,
        *cgsccAnalysisManager,
        *moduleAnalysisManager
    );

    passManager = new llvm::ModulePassManager(
        passBuilder->buildPerModuleDefaultPipeline(level)
    );
}

llvm::ModulePassManager *ModulePassManager::getLLVMPrimitive() {
    return passManager;
}

Napi::Value ModulePassManager::createFunctionPassManager(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    auto lto = (llvm::ThinOrFullLTOPhase) info[0].As<Napi::Number>().Uint32Value();

    auto fpm = new llvm::FunctionPassManager(
        passBuilder->buildFunctionSimplificationPipeline(level, lto)
    );

    return FunctionPassManager::New(env, fpm);
}

void ModulePassManager::addVerifierPass(const Napi::CallbackInfo& info)
{
    passManager->addPass(llvm::VerifierPass());
}

void ModulePassManager::addFunctionPasses(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    auto argsLen = info.Length();

    if (argsLen != 1) {
        throw Napi::TypeError::New(env, "(fpm: FunctionPassManager)");
    }

    auto fpm = FunctionPassManager::Extract(info[0]);

    if (!fpm) {
        throw Napi::TypeError::New(env, "(fpm: FunctionPassManager)");
    }

    passManager->addPass(llvm::createModuleToFunctionPassAdaptor(std::move(*fpm)));
}

Napi::Value ModulePassManager::isEmpty(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), passManager->isEmpty());
}

void ModulePassManager::run(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    auto argsLen = info.Length();

    if (argsLen != 1 || !Module::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "(module: Module)");
    }

    auto module = Module::Extract(info[0]);

    passManager->run(*module, *moduleAnalysisManager);
}

//===----------------------------------------------------------------------===//
//                        FunctionPassManager Class
//===----------------------------------------------------------------------===//

void FunctionPassManager::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FunctionPassManager", {
            InstanceMethod("addSROAPass", &FunctionPassManager::addSROAPass),
            InstanceMethod("addEarlyCSEPass", &FunctionPassManager::addEarlyCSEPass),
            InstanceMethod("addInstCombinePass", &FunctionPassManager::addInstCombinePass),
            InstanceMethod("isEmpty", &FunctionPassManager::isEmpty),
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), GlobalObject::constructor.Value());
    exports.Set("FunctionPassManager", func);
}

Napi::Object FunctionPassManager::New(Napi::Env env, llvm::FunctionPassManager *fpm) {
    return constructor.New({Napi::External<llvm::FunctionPassManager>::New(env, fpm)});
}

bool FunctionPassManager::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionPassManager *FunctionPassManager::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionPassManager::FunctionPassManager(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    auto external = info[0].As<Napi::External<llvm::FunctionPassManager>>();
    passManager = external.Data();
}

llvm::FunctionPassManager *FunctionPassManager::getLLVMPrimitive() {
    return passManager;
}

void FunctionPassManager::addSROAPass(const Napi::CallbackInfo &info) {
    passManager->addPass(llvm::SROAPass());
}

void FunctionPassManager::addEarlyCSEPass(const Napi::CallbackInfo &info) {
    bool useSSA = false;

    if (info.Length() >= 1 && info[0].IsBoolean()) {
        useSSA = info[0].As<Napi::Boolean>();
    }

    passManager->addPass(llvm::EarlyCSEPass(useSSA));
}

void FunctionPassManager::addInstCombinePass(const Napi::CallbackInfo& info) {
    passManager->addPass(llvm::InstCombinePass());
}

Napi::Value FunctionPassManager::isEmpty(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), passManager->isEmpty());
}
