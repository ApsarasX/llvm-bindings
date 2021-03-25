#include "IR/DataLayout.h"

void DataLayout::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DataLayout", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("DataLayout", func);
}

Napi::Object DataLayout::New(Napi::Env env, llvm::DataLayout *dl) {
    return constructor.New({Napi::External<llvm::DataLayout>::New(env, dl)});
}

bool DataLayout::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DataLayout &DataLayout::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DataLayout::DataLayout(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "DataLayout constructor needs to be called with new");
    }
    if (info.Length() == 0 || !(info[0].IsExternal() || info[0].IsString())) {
        throw Napi::TypeError::New(env, "DataLayout constructor needs to be called with new (latout: string)");
    }
    if (info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::DataLayout>>();
        dataLayout = new llvm::DataLayout(*external.Data());
    } else if (info[0].IsString()) {
        dataLayout = new llvm::DataLayout(std::string(info[0].As<Napi::String>()));
    }
}

llvm::DataLayout &DataLayout::getLLVMPrimitive() {
    return *dataLayout;
}

