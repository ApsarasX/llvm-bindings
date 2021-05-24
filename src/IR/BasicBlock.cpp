#include "IR/IR.h"
#include "Util/Util.h"

void BasicBlock::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "BasicBlock", {
            StaticMethod("Create", &BasicBlock::create),
            InstanceMethod("getParent", &BasicBlock::getParent),
            InstanceMethod("getModule", &BasicBlock::getModule),
            InstanceMethod("getTerminator", &BasicBlock::getTerminator),
            InstanceMethod("getFirstNonPHI", &BasicBlock::getFirstNonPHI),
            InstanceMethod("use_empty", &BasicBlock::useEmpty),
            InstanceMethod("deleteSelf", &BasicBlock::deleteSelf)
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
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::BasicBlock::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::BasicBlock>>();
    basicBlock = external.Data();
}

Napi::Value BasicBlock::create(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen == 0 ||
        !LLVMContext::IsClassOf(info[0]) ||
        argsLen >= 2 && !(info[1].IsString() || info[1].IsUndefined() || info[1].IsNull()) ||
        argsLen >= 3 && !Function::IsClassOf(info[2]) ||
        argsLen >= 4 && !BasicBlock::IsClassOf(info[3])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::BasicBlock::Create);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    std::string name;
    llvm::Function *parent = nullptr;
    llvm::BasicBlock *insertBefore = nullptr;
    if (argsLen >= 2 && info[1].IsString()) {
        name = info[1].As<Napi::String>();
    }
    if (argsLen >= 3) {
        parent = Function::Extract(info[2]);
    }
    if (argsLen >= 4) {
        insertBefore = BasicBlock::Extract(info[3]);
    }
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(context, name, parent, insertBefore);
    return BasicBlock::New(env, basicBlock);
}

llvm::BasicBlock *BasicBlock::getLLVMPrimitive() {
    return basicBlock;
}

Napi::Value BasicBlock::getParent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Function *function = basicBlock->getParent();
    if (function) {
        return Function::New(env, function);
    }
    return env.Null();
}

Napi::Value BasicBlock::getModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Module *module = basicBlock->getModule();
    if (module) {
        return Module::New(env, module);
    }
    return env.Null();
}

Napi::Value BasicBlock::getTerminator(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *termInst = basicBlock->getTerminator();
    if (termInst) {
        return Instruction::New(env, termInst);
    }
    return env.Null();
}

Napi::Value BasicBlock::getFirstNonPHI(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *nonPHIInst = basicBlock->getFirstNonPHI();
    if (nonPHIInst) {
        return Instruction::New(env, nonPHIInst);
    }
    return env.Null();
}

Napi::Value BasicBlock::useEmpty(const Napi::CallbackInfo &info) {
    return Napi::Boolean::New(info.Env(), basicBlock->use_empty());
}

void BasicBlock::deleteSelf(const Napi::CallbackInfo &info) {
    delete basicBlock;
    basicBlock = nullptr;
}
