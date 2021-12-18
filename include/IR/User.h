#pragma once

#include <napi.h>
#include <llvm/IR/User.h>

class User : public Napi::ObjectWrap<User> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::User *user);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::User *Extract(const Napi::Value &value);

    explicit User(const Napi::CallbackInfo &info);

    llvm::User *getLLVMPrimitive();

private:
    llvm::User *user = nullptr;

    Napi::Value getOperand(const Napi::CallbackInfo &info);

    void setOperand(const Napi::CallbackInfo &info);

    Napi::Value getNumOperands(const Napi::CallbackInfo &info);
};
