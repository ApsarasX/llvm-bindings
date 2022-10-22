#include "Target/index.h"
#include "IR/index.h"
#include "Util/index.h"

#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"

#include <iostream>

void TargetMachine::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "TargetMachine", {
            InstanceMethod("createDataLayout", &TargetMachine::createDataLayout),
            InstanceMethod("emitToFile", &TargetMachine::emitToFile),
            InstanceMethod("emitToBuffer", &TargetMachine::emitToBuffer)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("TargetMachine", func);
}

Napi::Object TargetMachine::New(Napi::Env env, llvm::TargetMachine *machine) {
    return constructor.New({Napi::External<llvm::TargetMachine>::New(env, machine)});
}

bool TargetMachine::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

TargetMachine::TargetMachine(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (info.IsConstructCall() && info.Length() == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::TargetMachine>>();
        targetMachine = external.Data();
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::TargetMachine::constructor);
}

Napi::Value TargetMachine::createDataLayout(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    const llvm::DataLayout &dataLayout = targetMachine->createDataLayout();
    return DataLayout::New(env, const_cast<llvm::DataLayout *>(&dataLayout));
}

void TargetMachine::emitToFile(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    auto fileName = info[1].As<Napi::String>().Utf8Value();
    std::error_code ec;
    llvm::raw_fd_ostream dest(fileName, ec, llvm::sys::fs::OF_None);

    auto module = Module::Extract(info[0]);
    auto type = (llvm::CodeGenFileType) info[2].As<Napi::Number>().Uint32Value();

    llvm::legacy::PassManager pm{};

    if (const_cast<llvm::TargetMachine*>(targetMachine)->addPassesToEmitFile(pm, dest, nullptr, type)) {
        throw Napi::TypeError::New(env, "cannot add emit pass");
    }

    pm.run(*module);
    dest.flush();
}

Napi::Value TargetMachine::emitToBuffer(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    llvm::SmallVector<char> buffer;
    llvm::raw_svector_ostream dest(buffer);

    auto module = Module::Extract(info[0]);
    auto type = (llvm::CodeGenFileType) info[1].As<Napi::Number>().Uint32Value();

    llvm::legacy::PassManager pm{};

    if (const_cast<llvm::TargetMachine*>(targetMachine)->addPassesToEmitFile(pm, dest, nullptr, type)) {
        throw Napi::TypeError::New(env, "cannot add emit pass");
    }

    pm.run(*module);

    return Napi::Value(env, Napi::Buffer<char>::New(env, buffer.data(), buffer.size()));
}
