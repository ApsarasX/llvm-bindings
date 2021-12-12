#include "IR/IR.h"
#include "Util/Util.h"

void DITypeRefArray::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DITypeRefArray", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("DITypeRefArray", func);
}

Napi::Value DITypeRefArray::New(Napi::Env env, llvm::DITypeRefArray *array) {
    return constructor.New({Napi::External<llvm::DITypeRefArray>::New(env, array)});
}

bool DITypeRefArray::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DITypeRefArray *DITypeRefArray::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DITypeRefArray::DITypeRefArray(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DITypeRefArray::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DITypeRefArray>>();
    array = external.Data();
}

llvm::DITypeRefArray *DITypeRefArray::getLLVMPrimitive() {
    return array;
}