#include "Support/Support.h"
#include "Util/Util.h"

void SMDiagnostic::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SMDiagnostic", {
    });
    constructor = Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("SMDiagnostic", func);
}

bool SMDiagnostic::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::SMDiagnostic &SMDiagnostic::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

SMDiagnostic::SMDiagnostic(const Napi::CallbackInfo &info) : Napi::ObjectWrap<SMDiagnostic>{info} {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::SMDiagnostic::constructor);
    }
    diagnostic = new llvm::SMDiagnostic();
}

llvm::SMDiagnostic &SMDiagnostic::getLLVMPrimitive() {
    return *diagnostic;
}