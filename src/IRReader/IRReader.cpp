#include <llvm/IRReader/IRReader.h>

#include "IRReader/IRReader.h"
#include "IR/IR.h"
#include "Support/Support.h"
#include "Util/Util.h"

Napi::Value parseIRFile(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 3 ||
        !info[0].IsString() ||
        !SMDiagnostic::IsClassOf(info[2]) ||
        !LLVMContext::IsClassOf(info[2])) {
        std::string filename = info[0].As<Napi::String>();
        llvm::SMDiagnostic &err = SMDiagnostic::Extract(info[1]);
        llvm::LLVMContext &context = LLVMContext::Extract(info[2]);
        llvm::Module *module = llvm::parseIRFile(filename, err, context).release();
        return Module::New(env, module);
    }
    throw Napi::TypeError::New(env, ErrMsg::Function::parseIRFile);
}

void InitIRReader(Napi::Env env, Napi::Object &exports) {
    exports.Set("parseIRFile", Napi::Function::New(env, parseIRFile));
}