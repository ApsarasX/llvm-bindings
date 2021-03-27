#include "IR/Instruction.h"
#include "IR/User.h"
#include "IR/Function.h"
#include "IR/Module.h"
#include "IR/BasicBlock.h"
#include "Util/Inherit.h"

void Instruction::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Instruction", {
            InstanceMethod("use_back", &Instruction::userBack),
            InstanceMethod("getParent", &Instruction::getParent),
            InstanceMethod("getModule", &Instruction::getModule),
            InstanceMethod("getFunction", &Instruction::getFunction)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), User::constructor.Value());
    exports.Set("Instruction", func);
}

Napi::Value Instruction::New(Napi::Env env, llvm::Instruction *instruction) {
    return constructor.New({Napi::External<llvm::Instruction>::New(env, instruction)});
}

bool Instruction::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Instruction *Instruction::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Instruction::Instruction(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Instruction.constructor needs to be called with new");
    }
    if (info.Length() < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected Instruction pointer");
    }
    auto external = info[0].As<Napi::External<llvm::Instruction>>();
    instruction = external.Data();
}

llvm::Instruction *Instruction::getLLVMPrimitive() {
    return instruction;
}

Napi::Value Instruction::userBack(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *userInst = instruction->user_back();
    if (userInst) {
        return Instruction::New(env, userInst);
    }
    return env.Null();
}

Napi::Value Instruction::getParent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::BasicBlock *basicBlock = instruction->getParent();
    if (basicBlock) {
        return BasicBlock::New(env, basicBlock);
    }
    return env.Null();
}

Napi::Value Instruction::getModule(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Module *module = instruction->getModule();
    if (module) {
        return Module::New(env, module);
    }
    return env.Null();
}

Napi::Value Instruction::getFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Function *function = instruction->getFunction();
    if (function) {
        return Function::New(env, function);
    }
    return env.Null();
}
