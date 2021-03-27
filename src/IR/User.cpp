#include "IR/User.h"
#include "IR/Value.h"
#include "IR/Constant.h"
#include "IR/Instruction.h"
#include "Util/Inherit.h"

void User::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "User", {
            InstanceMethod("getOperand", &User::getOperand),
            InstanceMethod("setOperand", &User::setOperand),
            InstanceMethod("getNumOperands", &User::getNumOperands),
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Value::constructor.Value());
    exports.Set("User", func);
}

Napi::Value User::New(Napi::Env env, llvm::User *user) {
    if (llvm::Constant::classof(user)) {
        return Constant::New(env, static_cast<llvm::Constant *>(user));
    } else if (llvm::Instruction::classof(user)) {
        return Instruction::New(env, static_cast<llvm::Instruction *>(user));
    }
    return constructor.New({Napi::External<llvm::User>::New(env, user)});
}

bool User::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::User *User::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

User::User(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Constructor needs to be called with new");
    }
    if (info.Length() < 1 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, "Expected user pointer");
    }
    auto external = info[0].As<Napi::External<llvm::User>>();
    user = external.Data();
}

Napi::Value User::getOperand(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, "User.getOperand needs to be called with: (i: unsigned)");
    }
    unsigned i = info[0].As<Napi::Number>();
    llvm::Value *operand = user->getOperand(i);
    return Value::New(env, operand);
}

void User::setOperand(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 2 || info[0].IsNumber() || !Value::IsClassOf(info[1])) {
        throw Napi::TypeError::New(env, "User.setOperand needs to be called with: (i: unsigned, val: Value)");
    }
    unsigned i = info[0].As<Napi::Number>();
    llvm::Value *value = Value::Extract(info[1]);
    user->setOperand(i, value);
}

Napi::Value User::getNumOperands(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned num = user->getNumOperands();
    return Napi::Number::New(env, num);
}

llvm::User *User::getLLVMPrimitive() {
    return user;
}
