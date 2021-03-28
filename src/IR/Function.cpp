#include "IR/Function.h"
#include "IR/GlobalObject.h"
#include "IR/FunctionType.h"
#include "IR/Module.h"
#include "IR/Argument.h"
#include "Util/Inherit.h"
#include "Util/ErrMsg.h"

void Function::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Function", {
            StaticMethod("Create", &Function::create),
            InstanceMethod("arg_size", &Function::argSize),
            InstanceMethod("getArg", &Function::getArg)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), GlobalObject::constructor.Value());
    exports.Set("Function", func);
}

Napi::Object Function::New(Napi::Env env, llvm::Function *function) {
    return constructor.New({Napi::External<llvm::Function>::New(env, function)});
}

bool Function::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Function *Function::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Function::Function(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Function::Create);
    }
    auto external = info[0].As<Napi::External<llvm::Function>>();
    function = external.Data();
}

Napi::Value Function::create(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen < 2 ||
        !FunctionType::IsClassOf(info[0]) ||
        !info[1].IsNumber() ||
        argsLen >= 3 && !info[2].IsString() ||
        argsLen >= 4 && !Module::IsClassOf(info[3])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Function::Create);
    }
    llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
    llvm::GlobalValue::LinkageTypes linkage = static_cast<llvm::GlobalValue::LinkageTypes>(info[1].As<Napi::Number>().Uint32Value());
    std::string name;
    llvm::Module *module = nullptr;
    if (argsLen >= 3) {
        name = info[2].As<Napi::String>();
    }
    if (argsLen >= 4) {
        module = Module::Extract(info[3]);
    }
    llvm::Function *function = llvm::Function::Create(funcType, linkage, name, module);
    return Function::New(env, function);
}

llvm::Function *Function::getLLVMPrimitive() {
    return function;
}

Napi::Value Function::argSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, function->arg_size());
}

Napi::Value Function::getArg(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && info[0].IsNumber()) {
        llvm::Argument *arg = function->getArg(info[0].As<Napi::Number>());
        return Argument::New(env, arg);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::Function::getArg);
}
