#include "IR/IR.h"
#include "Util/Util.h"

void ConstantStruct::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantStruct", {
            StaticMethod("get", &ConstantStruct::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantStruct", func);
}

Napi::Object ConstantStruct::New(Napi::Env env, llvm::ConstantStruct *constantStruct) {
    return constructor.New({Napi::External<llvm::ConstantStruct>::New(env, constantStruct)});
}

bool ConstantStruct::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantStruct *ConstantStruct::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantStruct::ConstantStruct(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantStruct::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ConstantStruct>>();
    constantStruct = external.Data();
}

llvm::ConstantStruct *ConstantStruct::getLLVMPrimitive() {
    return constantStruct;
}

Napi::Value ConstantStruct::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !StructType::IsClassOf(info[0]) || !info[1].IsArray()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ConstantStruct::get);
    }
    llvm::StructType *structType = StructType::Extract(info[0]);
    auto valuesArray = info[1].As<Napi::Array>();
    int numValues = valuesArray.Length();
    std::vector<llvm::Constant *> values(numValues);
    for (int i = 0; i < numValues; ++i) {
        values[i] = Constant::Extract(valuesArray.Get(i));
    }
    llvm::Constant *constantStruct = llvm::ConstantStruct::get(structType, values);
    return Constant::New(env, constantStruct);
}
