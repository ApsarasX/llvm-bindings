#include "IR/IR.h"
#include "Util/Util.h"

void DILocation::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DILocation", {
            StaticMethod("get", &DILocation::get)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DILocation", func);
}

Napi::Value DILocation::New(Napi::Env env, llvm::DILocation *location) {
    return constructor.New({Napi::External<llvm::DILocation>::New(env, location)});
}

bool DILocation::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILocation *DILocation::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILocation::DILocation(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILocation::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILocation>>();
    location = external.Data();
}

llvm::DILocation *DILocation::getLLVMPrimitive() {
    return location;
}

Napi::Value DILocation::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 4 && LLVMContext::IsClassOf(info[0]) && info[1].IsNumber() && info[2].IsNumber() && Metadata::IsClassOf(info[3])) {
        llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
        unsigned line = info[1].As<Napi::Number>();
        unsigned column = info[2].As<Napi::Number>();
        llvm::Metadata *metadata = Metadata::Extract(info[3]);
        llvm::DILocation *location = llvm::DILocation::get(context, line, column, metadata);
        return DILocation::New(env, location);
    } else if (info.Length() == 4 && LLVMContext::IsClassOf(info[0]) && info[1].IsNumber() && info[2].IsNumber() && DILocalScope::IsClassOf(info[3])) {
        llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
        unsigned line = info[1].As<Napi::Number>();
        unsigned column = info[2].As<Napi::Number>();
        llvm::DILocalScope *scope = DILocalScope::Extract(info[3]);
        llvm::DILocation *location = llvm::DILocation::get(context, line, column, scope);
        return DILocation::New(env, location);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DILocation::get);
}
