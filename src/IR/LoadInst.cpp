#include "IR/IR.h"
#include "Util/Util.h"

void LoadInst::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "LoadInst", {
            InstanceMethod("getType", &LoadInst::getType)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), Instruction::constructor.Value());
    exports.Set("LoadInst", func);
}

Napi::Object LoadInst::New(Napi::Env env, llvm::LoadInst *loadInst) {
    return constructor.New({Napi::External<llvm::LoadInst>::New(env, loadInst)});
}

bool LoadInst::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::LoadInst *LoadInst::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

LoadInst::LoadInst(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::LoadInst::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::LoadInst>>();
    loadInst = external.Data();
}

llvm::LoadInst *LoadInst::getLLVMPrimitive() {
    return loadInst;
}

Napi::Value LoadInst::getType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Type *type = loadInst->getType();
    return Type::New(env, type);
}
