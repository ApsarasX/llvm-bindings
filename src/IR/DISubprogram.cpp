#include "IR/IR.h"
#include "Util/Util.h"

void DISubprogram::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DISubprogram", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DILocalScope::constructor.Value());
    exports.Set("DISubprogram", func);
}

Napi::Value DISubprogram::New(Napi::Env env, llvm::DISubprogram *subProgram) {
    return constructor.New({Napi::External<llvm::DISubprogram>::New(env, subProgram)});
}

bool DISubprogram::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DISubprogram *DISubprogram::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DISubprogram::DISubprogram(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DISubprogram::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DISubprogram>>();
    subprogram = external.Data();
}

llvm::DISubprogram *DISubprogram::getLLVMPrimitive() {
    return subprogram;
}