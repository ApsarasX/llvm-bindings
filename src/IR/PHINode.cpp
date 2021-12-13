#include "IR/IR.h"
#include "Util/Util.h"

void PHINode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "PHINode", {
            InstanceMethod("addIncoming", &PHINode::addIncoming),
            InstanceMethod("setDebugLoc", &PHINode::setDebugLoc)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("PHINode", func);
}

Napi::Object PHINode::New(Napi::Env env, llvm::PHINode *phiNode) {
    return constructor.New({Napi::External<llvm::PHINode>::New(env, phiNode)});
}

bool PHINode::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::PHINode *PHINode::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

PHINode::PHINode(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::PHINode::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::PHINode>>();
    phiNode = external.Data();
}

llvm::PHINode *PHINode::getLLVMPrimitive() {
    return phiNode;
}

void PHINode::addIncoming(const Napi::CallbackInfo &info) {
    if (info.Length() >= 2 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::BasicBlock *basicBlock = BasicBlock::Extract(info[1]);
        phiNode->addIncoming(value, basicBlock);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::PHINode::addIncoming);
}

void PHINode::setDebugLoc(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && DebugLoc::IsClassOf(info[0])) {
        llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
        phiNode->setDebugLoc(*location);
        return;
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::PHINode::setDebugLoc);
}