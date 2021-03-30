#include <llvm/IR/Verifier.h>

#include "IR/IR.h"
#include "Util/Util.h"

Napi::Value verifyFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Function::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Function::verifyFunction);
    }
    llvm::Function *func = Function::Extract(info[0]);
    bool result = llvm::verifyFunction(*func, &llvm::errs());
    return Napi::Boolean::New(env, result);
}

Napi::Value verifyModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !Module::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Function::verifyModule);
    }
    llvm::Module *module = Module::Extract(info[0]);
    bool result = llvm::verifyModule(*module, &llvm::errs());
    return Napi::Boolean::New(env, result);
}


void InitVerifier(Napi::Env env, Napi::Object &exports) {
    exports.Set("verifyFunction", Napi::Function::New(env, verifyFunction));
    exports.Set("verifyModule", Napi::Function::New(env, verifyModule));
}