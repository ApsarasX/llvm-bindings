#include "Linker/Linker.h"
#include "IR/index.h"
#include "Util/index.h"

void Linker::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Linker", {
            InstanceMethod("linkInModule", &Linker::linkInModule),
            StaticMethod("linkModules", &Linker::linkModules),
    });
    constructor = Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Linker", func);
}

Linker::Linker(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (info.IsConstructCall() && info.Length() == 1 && Module::IsClassOf(info[0])) {
        llvm::Module &module = *Module::Extract(info[0]);
        linker = new llvm::Linker(module);
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Linker::constructor);
}

Napi::Value Linker::linkInModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && Module::IsClassOf(info[0])) {
        llvm::Module *srcModule = Module::Extract(info[0]);
        bool failed = linker->linkInModule(std::unique_ptr<llvm::Module>(srcModule));
        return Napi::Boolean::New(env, failed);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Linker::linkInModule);
}

Napi::Value Linker::linkModules(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && Module::IsClassOf(info[0]) && Module::IsClassOf(info[1])) {
        llvm::Module &destModule = *Module::Extract(info[0]);
        llvm::Module *srcModule = Module::Extract(info[1]);
        bool failed = llvm::Linker::linkModules(destModule, std::unique_ptr<llvm::Module>(srcModule));
        return Napi::Boolean::New(env, failed);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Linker::linkModules);
}
