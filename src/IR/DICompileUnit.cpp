#include "IR/IR.h"
#include "Util/Util.h"

void DICompileUnit::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DICompileUnit", {
            InstanceMethod("getFile", &DICompileUnit::getFile)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DICompileUnit", func);
}

Napi::Value DICompileUnit::New(Napi::Env env, llvm::DICompileUnit *unit) {
    return constructor.New({Napi::External<llvm::DICompileUnit>::New(env, unit)});
}

bool DICompileUnit::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DICompileUnit *DICompileUnit::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DICompileUnit::DICompileUnit(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DICompileUnit::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DICompileUnit>>();
    unit = external.Data();
}

llvm::DICompileUnit *DICompileUnit::getLLVMPrimitive() {
    return unit;
}

Napi::Value DICompileUnit::getFile(const Napi::CallbackInfo &info) {
    return DIFile::New(info.Env(), unit->getFile());
}
