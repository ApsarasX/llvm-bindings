#include "IR/IR.h"
#include "Util/Util.h"

void DILocalScope::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DILocalScope", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DILocalScope", func);
}

Napi::Value DILocalScope::New(Napi::Env env, llvm::DILocalScope *scope) {
    if (llvm::isa<llvm::DISubprogram>(scope)) {
        return DISubprogram::New(env, llvm::cast<llvm::DISubprogram>(scope));
    }
    return constructor.New({Napi::External<llvm::DILocalScope>::New(env, scope)});
}

bool DILocalScope::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILocalScope *DILocalScope::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILocalScope::DILocalScope(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILocalScope::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILocalScope>>();
    scope = external.Data();
}

llvm::DILocalScope *DILocalScope::getLLVMPrimitive() {
    return scope;
}