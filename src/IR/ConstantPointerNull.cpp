#include "IR/ConstantPointerNull.h"
#include "IR/Constant.h"
#include "IR/PointerType.h"
#include "Util/Inherit.h"

void ConstantPointerNull::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ConstantPointerNull", {
            StaticMethod("get", &ConstantPointerNull::get),
            InstanceMethod("getType", &ConstantPointerNull::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Constant::constructor.Value());
    exports.Set("ConstantPointerNull", func);
}

Napi::Object ConstantPointerNull::New(Napi::Env env, llvm::ConstantPointerNull *constantPointerNull) {
    return constructor.New({Napi::External<llvm::ConstantPointerNull>::New(env, constantPointerNull)});
}

bool ConstantPointerNull::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ConstantPointerNull *ConstantPointerNull::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ConstantPointerNull::ConstantPointerNull(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "ConstantPointerNull.constructor needs to be called with new");
    }
    if (info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "ConstantPointerNull.constructor needs to ce called with new (constantPointerNull: ConstantPointerNull)");
    }
    auto external = info[0].As<Napi::External<llvm::ConstantPointerNull>>();
    constantPointerNull = external.Data();
}

llvm::ConstantPointerNull *ConstantPointerNull::getLLVMPrimitive() {
    return constantPointerNull;
}

Napi::Value ConstantPointerNull::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !PointerType::IsClassOf(info[0])) {
        llvm::PointerType *type = PointerType::Extract(info[0]);
        return ConstantPointerNull::New(env, llvm::ConstantPointerNull::get(type));
    }
    throw Napi::TypeError::New(env, "ConstantPointerNull.get needs to be called with (type: PointerType)");
}

Napi::Value ConstantPointerNull::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::PointerType *type = constantPointerNull->getType();
    return PointerType::New(env, type);
}
