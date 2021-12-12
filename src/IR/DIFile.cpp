#include "IR/IR.h"
#include "Util/Util.h"

void DIFile::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIFile", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DIFile", func);
}

Napi::Value DIFile::New(Napi::Env env, llvm::DIFile *file) {
    return constructor.New({Napi::External<llvm::DIFile>::New(env, file)});
}

bool DIFile::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIFile *DIFile::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIFile::DIFile(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIFile::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIFile>>();
    file = external.Data();
}

llvm::DIFile *DIFile::getLLVMPrimitive() {
    return file;
}