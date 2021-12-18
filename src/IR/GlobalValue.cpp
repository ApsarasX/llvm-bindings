#include "IR/index.h"
#include "Util/index.h"

void GlobalValue::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Object linkageTypes = Napi::Object::New(env);
    linkageTypes.Set("ExternalLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::ExternalLinkage));
    linkageTypes.Set("AvailableExternallyLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::AvailableExternallyLinkage));
    linkageTypes.Set("LinkOnceAnyLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::LinkOnceAnyLinkage));
    linkageTypes.Set("LinkOnceODRLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::LinkOnceODRLinkage));
    linkageTypes.Set("WeakAnyLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::WeakAnyLinkage));
    linkageTypes.Set("WeakODRLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::WeakODRLinkage));
    linkageTypes.Set("AppendingLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::AppendingLinkage));
    linkageTypes.Set("InternalLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::InternalLinkage));
    linkageTypes.Set("PrivateLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::PrivateLinkage));
    linkageTypes.Set("ExternalWeakLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::ExternalWeakLinkage));
    linkageTypes.Set("CommonLinkage", Napi::Number::New(env, llvm::GlobalValue::LinkageTypes::CommonLinkage));
    Napi::Object visibilityTypes = Napi::Object::New(env);
    visibilityTypes.Set("DefaultVisibility", Napi::Number::New(env, llvm::GlobalValue::VisibilityTypes::DefaultVisibility));
    visibilityTypes.Set("HiddenVisibility", Napi::Number::New(env, llvm::GlobalValue::VisibilityTypes::HiddenVisibility));
    visibilityTypes.Set("ProtectedVisibility", Napi::Number::New(env, llvm::GlobalValue::VisibilityTypes::ProtectedVisibility));
    Napi::Function func = DefineClass(env, "GlobalValue", {
            StaticValue("LinkageTypes", linkageTypes),
            StaticValue("VisibilityTypes", visibilityTypes)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("GlobalValue", func);
}

Napi::Object GlobalValue::New(Napi::Env env, llvm::GlobalValue *globalValue) {
    if (llvm::isa<llvm::GlobalObject>(globalValue)) {
        return GlobalObject::New(env, llvm::cast<llvm::GlobalObject>(globalValue));
    }
    return constructor.New({Napi::External<llvm::GlobalValue>::New(env, globalValue)});
}

bool GlobalValue::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::GlobalValue *GlobalValue::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

GlobalValue::GlobalValue(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::GlobalValue::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::GlobalValue>>();
    globalValue = external.Data();
}

llvm::GlobalValue *GlobalValue::getLLVMPrimitive() {
    return globalValue;
}
