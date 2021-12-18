#include "IR/index.h"
#include "Util/index.h"

void GlobalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "GlobalVariable", {
            InstanceMethod("getType", &GlobalVariable::getType),
            InstanceMethod("removeFromParent", &GlobalVariable::removeFromParent),
            InstanceMethod("eraseFromParent", &GlobalVariable::eraseFromParent),
            InstanceMethod("addDebugInfo", &GlobalVariable::addDebugInfo)
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
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

GlobalVariable::GlobalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::GlobalVariable::constructor);
    }
    unsigned argsLen = info.Length();
    if (argsLen >= 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::GlobalVariable>>();
        globalVariable = external.Data();
        return;
    } else if (argsLen >= 3 &&
               Type::IsClassOf(info[0]) &&
               info[1].IsBoolean() &&
               info[2].IsNumber()) {
        if (argsLen == 3 ||
            argsLen >= 4 && Constant::IsClassOf(info[3]) ||
            argsLen >= 5 && info[4].IsString()) {
            llvm::Type *type = Type::Extract(info[0]);
            bool isConstant = info[1].As<Napi::Boolean>();
            llvm::GlobalValue::LinkageTypes linkage = static_cast<llvm::GlobalValue::LinkageTypes>(info[2].As<Napi::Number>().Uint32Value());
            llvm::Constant *initializer = argsLen >= 4 ? Constant::Extract(info[3]) : nullptr;
            std::string name = argsLen >= 5 ? std::string(info[4].As<Napi::String>()) : "";
            globalVariable = new llvm::GlobalVariable(type, isConstant, linkage, initializer, name);
            return;
        }
    } else if (argsLen >= 5 &&
               Module::IsClassOf(info[0]) &&
               Type::IsClassOf(info[1]) &&
               info[2].IsBoolean() &&
               info[3].IsNumber() &&
               Constant::IsClassOf(info[4])) {
        if (argsLen == 5 || argsLen >= 6 && info[5].IsString()) {
            llvm::Module *module = Module::Extract(info[0]);
            llvm::Type *type = Type::Extract(info[1]);
            bool isConstant = info[2].As<Napi::Boolean>();
            llvm::GlobalValue::LinkageTypes linkage = static_cast<llvm::GlobalValue::LinkageTypes>(info[3].As<Napi::Number>().Uint32Value());
            llvm::Constant *initializer = Constant::Extract(info[4]);
            std::string name = argsLen >= 6 ? std::string(info[5].As<Napi::String>()) : "";
            globalVariable = new llvm::GlobalVariable(*module, type, isConstant, linkage, initializer, name);
            return;
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::GlobalVariable::constructor);
}

llvm::GlobalVariable *GlobalVariable::getLLVMPrimitive() {
    return globalVariable;
}

Napi::Value GlobalVariable::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = globalVariable->getType();
    return Type::New(env, type);
}

void GlobalVariable::removeFromParent(const Napi::CallbackInfo &info) {
    globalVariable->removeFromParent();
}

void GlobalVariable::eraseFromParent(const Napi::CallbackInfo &info) {
    globalVariable->eraseFromParent();
}

void GlobalVariable::addDebugInfo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && DIGlobalVariableExpression::IsClassOf(info[0])) {
        llvm::DIGlobalVariableExpression *gv = DIGlobalVariableExpression::Extract(info[0]);
        globalVariable->addDebugInfo(gv);
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::GlobalVariable::addDebugInfo);
}
