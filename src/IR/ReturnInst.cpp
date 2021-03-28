#include "IR/IR.h"
#include "Util/Util.h"

void ReturnInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ReturnInst", {
            InstanceMethod("getReturnValue", &ReturnInst::getReturnValue)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("ReturnInst", func);
}

Napi::Object ReturnInst::New(Napi::Env env, llvm::ReturnInst *returnInst) {
    return constructor.New({Napi::External<llvm::ReturnInst>::New(env, returnInst)});
}

bool ReturnInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::ReturnInst *ReturnInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

ReturnInst::ReturnInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::ReturnInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::ReturnInst>>();
    returnInst = external.Data();
}

llvm::ReturnInst *ReturnInst::getLLVMPrimitive() {
    return returnInst;
}

Napi::Value ReturnInst::getReturnValue(const Napi::CallbackInfo &info) {
    return Value::New(info.Env(), returnInst->getReturnValue());
}
