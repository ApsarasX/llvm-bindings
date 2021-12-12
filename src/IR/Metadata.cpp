#include "IR/IR.h"
#include "Util/Util.h"

void Metadata::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Metadata", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Metadata", func);
}

Napi::Value Metadata::New(Napi::Env env, llvm::Metadata *metadata) {
    if (llvm::isa<llvm::MDNode>(metadata)) {
        return MDNode::New(env, llvm::cast<llvm::MDNode>(metadata));
    }
    return constructor.New({Napi::External<llvm::Metadata>::New(env, metadata)});
}

bool Metadata::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Metadata *Metadata::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Metadata::Metadata(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Metadata::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::Metadata>>();
    metadata = external.Data();
}

llvm::Metadata *Metadata::getLLVMPrimitive() {
    return metadata;
}