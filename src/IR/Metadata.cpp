#include "IR/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
//                        Metadata Class
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
//                        MDNode Class
//===----------------------------------------------------------------------===//

void MDNode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "MDNode", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Metadata::constructor.Value());
    exports.Set("MDNode", func);
}

Napi::Value MDNode::New(Napi::Env env, llvm::MDNode *node) {
    if (llvm::isa<llvm::DIExpression>(node)) {
        return DIExpression::New(env, llvm::cast<llvm::DIExpression>(node));
    } else if (llvm::isa<llvm::DIGlobalVariableExpression>(node)) {
        return DIGlobalVariableExpression::New(env, llvm::cast<llvm::DIGlobalVariableExpression>(node));
    } else if (llvm::isa<llvm::DILocation>(node)) {
        return DILocation::New(env, llvm::cast<llvm::DILocation>(node));
    } else if (llvm::isa<llvm::DINode>(node)) {
        return DINode::New(env, llvm::cast<llvm::DINode>(node));
    }
    return constructor.New({Napi::External<llvm::MDNode>::New(env, node)});
}

bool MDNode::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::MDNode *MDNode::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

MDNode::MDNode(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::MDNode::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::MDNode>>();
    node = external.Data();
}

llvm::MDNode *MDNode::getLLVMPrimitive() {
    return node;
}

//===----------------------------------------------------------------------===//
//                        LLVMConstants Namespace
//===----------------------------------------------------------------------===//

void LLVMConstants::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object constantsNS = Napi::Object::New(env);
    constantsNS.Set("DEBUG_METADATA_VERSION", Napi::Number::New(env, llvm::LLVMConstants::DEBUG_METADATA_VERSION));
    exports.Set("LLVMConstants", constantsNS);
}
