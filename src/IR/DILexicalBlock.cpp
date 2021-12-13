#include "IR/IR.h"
#include "Util/Util.h"

void DILexicalBlock::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope block(env);
    Napi::Function func = DefineClass(env, "DILexicalBlock", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DILocalScope::constructor.Value());
    exports.Set("DILexicalBlock", func);
}

Napi::Value DILexicalBlock::New(Napi::Env env, llvm::DILexicalBlock *block) {
    if (llvm::isa<llvm::DISubprogram>(block)) {
        return DISubprogram::New(env, llvm::cast<llvm::DISubprogram>(block));
    }
    return constructor.New({Napi::External<llvm::DILexicalBlock>::New(env, block)});
}

bool DILexicalBlock::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILexicalBlock *DILexicalBlock::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILexicalBlock::DILexicalBlock(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILexicalBlock::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILexicalBlock>>();
    block = external.Data();
}

llvm::DILexicalBlock *DILexicalBlock::getLLVMPrimitive() {
    return block;
}