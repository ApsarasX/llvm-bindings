#include "IR/IR.h"
#include "Util/Util.h"

void DINode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DINode", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DINode", func);
}

Napi::Value DINode::New(Napi::Env env, llvm::DINode *node) {
    if (llvm::isa<llvm::DIScope>(node)) {
        return DIScope::New(env, llvm::cast<llvm::DIScope>(node));
    } else if (llvm::isa<llvm::DIVariable>(node)) {
        return DIVariable::New(env, llvm::cast<llvm::DIVariable>(node));
    }
    return constructor.New({Napi::External<llvm::DINode>::New(env, node)});
}

bool DINode::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DINode *DINode::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DINode::DINode(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DINode::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DINode>>();
    node = external.Data();
}

llvm::DINode *DINode::getLLVMPrimitive() {
    return node;
}