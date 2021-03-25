#include "IR/Verifier.h"
#include "IR/Function.h"
#include "IR/Module.h"

Napi::Value verifyFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Function::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "verifyFunction needs to be called with (func: Function)");
    }
    llvm::Function *func = Function::Extract(info[0]);
    bool result = llvm::verifyFunction(*func);
    return Napi::Boolean::New(env, result);
}

Napi::Value verifyModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Module::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "verifyModule needs to be called with (module: Module)");
    }
    llvm::Module *module = Module::Extract(info[0]);
    bool result = llvm::verifyModule(*module);
    return Napi::Boolean::New(env, result);
}


void InitVerifier(Napi::Env env, Napi::Object &exports) {
    exports.Set("verifyFunction", Napi::Function::New(env, verifyFunction));
    exports.Set("verifyModule", Napi::Function::New(env, verifyModule));
}