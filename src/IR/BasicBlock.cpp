#include "IR/BasicBlock.h"
#include "IR/Value.h"
#include "IR/LLVMContext.h"
#include "IR/Function.h"
#include "Util/Inherit.h"

void BasicBlock::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "BasicBlock", {
            StaticMethod("Create", &BasicBlock::create)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Value::constructor.Value());
    exports.Set("BasicBlock", func);
}

Napi::Object BasicBlock::New(Napi::Env env, llvm::BasicBlock *basicBlock) {
    return constructor.New({Napi::External<llvm::BasicBlock>::New(env, basicBlock)});
}

bool BasicBlock::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::BasicBlock *BasicBlock::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

BasicBlock::BasicBlock(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Constructor needs to be called with new");
    }
    if (info.Length() < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected basic block pointer");
    }
    auto external = info[0].As<Napi::External<llvm::BasicBlock>>();
    basicBlock = external.Data();
}

Napi::Value BasicBlock::create(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    const std::string &errMsg = "BasicBlock.Create needs to be called with: (context: LLVMContext, name?: string, parent?: Function, insertBefore?: BasicBlock)";
    if (argsLen < 1 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, errMsg);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    std::string name;
    llvm::Function *parent = nullptr;
    llvm::BasicBlock *insertBefore = nullptr;
    if (argsLen >= 2) {
        if (!info[1].IsString()) {
            throw Napi::TypeError::New(env, errMsg);
        }
        name = info[1].As<Napi::String>();
    }
    if (argsLen >= 3) {
        if (!Function::IsClassOf(info[2].As<Napi::Object>())) {
            throw Napi::TypeError::New(env, errMsg);
        }
        parent = Function::Extract(info[2]);
    }
    if (argsLen >= 4) {
        if (!BasicBlock::IsClassOf(info[3].As<Napi::Object>())) {
            throw Napi::TypeError::New(env, errMsg);
        }
        insertBefore = BasicBlock::Extract(info[3]);
    }
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(context, name, parent, insertBefore);
    return BasicBlock::New(env, basicBlock);
}

llvm::BasicBlock *BasicBlock::getLLVMPrimitive() {
    return basicBlock;
}