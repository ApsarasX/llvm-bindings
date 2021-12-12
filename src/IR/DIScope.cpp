#include "IR/IR.h"
#include "Util/Util.h"

void DIScope::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIScope", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DINode::constructor.Value());
    exports.Set("DIScope", func);
}

Napi::Value DIScope::New(Napi::Env env, llvm::DIScope *scope) {
    if (llvm::isa<llvm::DICompileUnit>(scope)) {
        return DICompileUnit::New(env, llvm::cast<llvm::DICompileUnit>(scope));
    } else if (llvm::isa<llvm::DIFile>(scope)) {
        return DIFile::New(env, llvm::cast<llvm::DIFile>(scope));
    } else if (llvm::isa<llvm::DILocalScope>(scope)) {
        return DILocalScope::New(env, llvm::cast<llvm::DILocalScope>(scope));
    } else if (llvm::isa<llvm::DIType>(scope)) {
        return DIType::New(env, llvm::cast<llvm::DIType>(scope));
    }
    return constructor.New({Napi::External<llvm::DIScope>::New(env, scope)});
}

bool DIScope::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIScope *DIScope::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIScope::DIScope(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIScope::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIScope>>();
    scope = external.Data();
}

llvm::DIScope *DIScope::getLLVMPrimitive() {
    return scope;
}