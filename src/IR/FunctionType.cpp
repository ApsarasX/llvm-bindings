#include "IR/IR.h"
#include "Util/Util.h"

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
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::FunctionType>>();
    functionType = external.Data();
}

Napi::Value FunctionType::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (!(argsLen == 2 && Type::IsClassOf(info[0]) && info[1].IsBoolean()) &&
        !(argsLen >= 3 && Type::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsBoolean())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::FunctionType::get);
    }
    llvm::Type *returnType = Type::Extract(info[0]);
    bool isVarArg = info[argsLen == 2 ? 1 : 2].As<Napi::Boolean>();
    llvm::FunctionType *functionType;
    if (argsLen >= 3) {
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
