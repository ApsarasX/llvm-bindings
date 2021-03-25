#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

#include "Bitcode/BitcodeWriter.h"
#include "IR/Module.h"

void WriteBitcodeToFile(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2 || !Module::IsClassOf(info[0]) || !info[1].IsString()) {
        throw Napi::TypeError::New(env, "writeBitcodeToFile needs to be called with: module: Module, filename: string");
    }

    llvm::Module *module = Module::Extract(info[0]);
    std::string fileName = info[1].As<Napi::String>();

    std::error_code errorCode;
    llvm::raw_fd_ostream byteCodeFile(fileName, errorCode, llvm::sys::fs::F_None);

    if (errorCode) {
        throw Napi::TypeError::New(env, "Failed to open file: " + errorCode.message());
    }
    llvm::WriteBitcodeToFile(*module, byteCodeFile);
    byteCodeFile.flush();
    byteCodeFile.close();
}

void InitBitcodeWriter(Napi::Env env, Napi::Object &exports) {
    exports.Set("writeBitcodeToFile", Napi::Function::New(env, WriteBitcodeToFile));
}