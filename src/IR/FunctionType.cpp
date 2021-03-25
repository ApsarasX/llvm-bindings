#include <vector>
#include "IR/Type.h"
#include "IR/FunctionType.h"
#include "Util/Inherit.h"

void FunctionType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FunctionType", {
            StaticMethod("get", &FunctionType::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Type::constructor.Value());
    exports.Set("FunctionType", func);
}

Napi::Object FunctionType::New(Napi::Env env, llvm::FunctionType *type) {
    return constructor.New({Napi::External<llvm::FunctionType>::New(env, type)});
}

bool FunctionType::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::FunctionType *FunctionType::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

FunctionType::FunctionType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Constructor needs to be called with new");
    }
    if (info.Length() < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected function type pointer");
    }
    auto external = info[0].As<Napi::External<llvm::FunctionType>>();
    functionType = external.Data();
}

Napi::Value FunctionType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (!(info.Length() == 2 && Type::IsClassOf(info[0]) && info[1].IsBoolean()) &&
        !(info.Length() == 3 && Type::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsBoolean())) {
        const std::string message = "FunctionType.get needs to be called with: (returnType: Type, isVarArg: boolean) or (returnType: Type, paramTypes: Type[], isVarArg: boolean)";
        throw Napi::TypeError::New(env, message);
    }
    llvm::Type *returnType = Type::Extract(info[0]);
    bool isVarArg = info[info.Length() - 1].As<Napi::Boolean>();
    llvm::FunctionType *functionType;
    if (info.Length() == 3) {
        auto paramsArray = info[1].As<Napi::Array>();
        int numParams = paramsArray.Length();
        std::vector<llvm::Type *> paramTypes(numParams);
        for (int i = 0; i < numParams; ++i) {
            paramTypes[i] = Type::Extract(paramsArray.Get(i));
        }
        functionType = llvm::FunctionType::get(returnType, paramTypes, isVarArg);
    } else {
        functionType = llvm::FunctionType::get(returnType, isVarArg);
    }
    return FunctionType::New(env, functionType);
}

llvm::FunctionType *FunctionType::getLLVMPrimitive() {
    return functionType;
}
