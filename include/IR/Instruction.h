#pragma once

#include <napi.h>
#include <llvm/IR/Instruction.h>

class Instruction : public Napi::ObjectWrap<Instruction> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT

    static void Init(Napi::Env env, Napi::Object &exports);

    static Napi::Value New(Napi::Env env, llvm::Instruction *instruction);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::Instruction *Extract(const Napi::Value &value);

    explicit Instruction(const Napi::CallbackInfo &info);

    llvm::Instruction *getLLVMPrimitive();

private:
    llvm::Instruction *instruction = nullptr;

    Napi::Value userBack(const Napi::CallbackInfo &info);

    Napi::Value getParent(const Napi::CallbackInfo &info);

    Napi::Value getModule(const Napi::CallbackInfo &info);

    Napi::Value getFunction(const Napi::CallbackInfo &info);
};

