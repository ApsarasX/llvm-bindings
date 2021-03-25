#include "IR/GlobalVariable.h"
#include "IR/GlobalObject.h"
#include "IR/Module.h"
#include "IR/Type.h"
#include "IR/Constant.h"
#include "Util/Inherit.h"

void GlobalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "GlobalVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), GlobalObject::constructor.Value());
    exports.Set("GlobalVariable", func);
}

Napi::Object GlobalVariable::New(Napi::Env env, llvm::GlobalVariable *variable) {
    return constructor.New({Napi::External<llvm::GlobalVariable>::New(env, variable)});
}

bool GlobalVariable::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::GlobalVariable *GlobalVariable::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

GlobalVariable::GlobalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "GlobalVariable constructor needs to be called with new");
    }
    int argsLen = info.Length();
    if (argsLen == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::GlobalVariable>>();
        globalVariable = external.Data();
    } else if (argsLen >= 4 && Module::IsClassOf(info[0]) && Type::IsClassOf(info[1]) && info[2].IsBoolean() && info[3].IsNumber()) {
        if ((argsLen < 5 || Constant::IsClassOf(info[4])) && (argsLen < 6 || info[5].IsString())) {
            llvm::Module *module = Module::Extract(info[0]);
            llvm::Type *type = Type::Extract(info[1]);
            bool isConstant = info[2].As<Napi::Boolean>();
            llvm::GlobalValue::LinkageTypes linkage = static_cast<llvm::GlobalValue::LinkageTypes>(info[3].As<Napi::Number>().Uint32Value());
            llvm::Constant *initializer = argsLen >= 5 ? Constant::Extract(info[4]) : nullptr;
            std::string name = argsLen >= 6 ? std::string(info[5].As<Napi::String>()) : "";
            globalVariable = new llvm::GlobalVariable(*module, type, isConstant, linkage, initializer, name);
        }
    }
    throw Napi::TypeError::New(env, "GlobalVariable constructor needs to be called with " \
        "new (gv: GlobalVariable) or" \
        "new (module: Module, type: Type, isConstant: boolean, linkage: LinkageTypes, initializer?: Constant, name?: string)");
}

llvm::GlobalVariable *GlobalVariable::getLLVMPrimitive() {
    return globalVariable;
}