#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

#include "Bitcode/Bitcode.h"
#include "IR/IR.h"
#include "Util/Util.h"

void writeBitcodeToFile(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !Module::IsClassOf(info[0]) || !info[1].IsString()) {
        throw Napi::TypeError::New(env, ErrMsg::Function::WriteBitcodeToFile);
    }
    llvm::Module *module = Module::Extract(info[0]);
    std::string fileName = info[1].As<Napi::String>();
    std::error_code errorCode;
    llvm::raw_fd_ostream byteCodeFile(fileName, errorCode, llvm::sys::fs::F_None);
    if (errorCode) {
        throw Napi::TypeError::New(env, errorCode.message() + ": " + fileName);
    }
    llvm::WriteBitcodeToFile(*module, byteCodeFile);
    byteCodeFile.flush();
    byteCodeFile.close();
}

void InitBitcodeWriter(Napi::Env env, Napi::Object &exports) {
    exports.Set("WriteBitcodeToFile", Napi::Function::New(env, writeBitcodeToFile));
}