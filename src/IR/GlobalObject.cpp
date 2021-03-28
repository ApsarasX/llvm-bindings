#include "IR/IR.h"
#include "Util/Util.h"

void GlobalObject::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "GlobalObject", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), GlobalValue::constructor.Value());
    exports.Set("GlobalObject", func);
}

Napi::Object GlobalObject::New(Napi::Env env, llvm::GlobalObject *globalObject) {
    if (llvm::Function::classof(globalObject)) {
        return Function::New(env, static_cast<llvm::Function *>(globalObject));
    } else if (llvm::GlobalVariable::classof(globalObject)) {
        return GlobalVariable::New(env, static_cast<llvm::GlobalVariable *>(globalObject));
    }
    return constructor.New({Napi::External<llvm::GlobalObject>::New(env, globalObject)});
}

bool GlobalObject::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::GlobalObject *GlobalObject::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

GlobalObject::GlobalObject(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::GlobalObject::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::GlobalObject>>();
    globalObject = external.Data();
}

llvm::GlobalObject *GlobalObject::getLLVMPrimitive() {
    return globalObject;
}
