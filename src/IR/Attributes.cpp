#include "IR/index.h"
#include "Util/index.h"

void Attribute::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);

    Napi::Object attributeKinds = Napi::Object::New(env);
    attributeKinds.Set("ByVal", Napi::Number::New(env, llvm::Attribute::AttrKind::ByVal));
    attributeKinds.Set("InReg", Napi::Number::New(env, llvm::Attribute::AttrKind::InReg));
    attributeKinds.Set("NoAlias", Napi::Number::New(env, llvm::Attribute::AttrKind::NoAlias));
    attributeKinds.Set("NoInline", Napi::Number::New(env, llvm::Attribute::AttrKind::NoInline));
    attributeKinds.Set("NoUnwind", Napi::Number::New(env, llvm::Attribute::AttrKind::NoUnwind));
    attributeKinds.Set("ReadOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::ReadOnly));
    attributeKinds.Set("SExt", Napi::Number::New(env, llvm::Attribute::AttrKind::SExt));
    attributeKinds.Set("NoRecurse", Napi::Number::New(env, llvm::Attribute::AttrKind::NoRecurse));
    attributeKinds.Set("NonNull", Napi::Number::New(env, llvm::Attribute::AttrKind::NonNull));

    Napi::Function func = DefineClass(env, "Attribute", {
        StaticValue("AttrKind", attributeKinds),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Attribute", func);
}

bool Attribute::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Attribute *Attribute::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }

    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Attribute::Attribute(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    auto env = info.Env();
    unsigned argsLen = info.Length();

    if (info.IsConstructCall() && argsLen >= 2 && argsLen <= 3 && LLVMContext::IsClassOf(info[0]) && info[1].IsNumber()) {
        llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
        auto attributeKind = static_cast<llvm::Attribute::AttrKind>((unsigned)info[1].As<Napi::Number>());
        
        if (argsLen == 2) {
            attribute = llvm::Attribute::get(context, attributeKind);
            return;
        }
        
        if (Type::IsClassOf(info[2])) {
            auto type = Type::Extract(info[2]);
            attribute = llvm::Attribute::get(context, attributeKind, type);
            return;
        }
    }

    throw Napi::TypeError::New(env, ErrMsg::Class::Attribute::constructor);
}

llvm::Attribute *Attribute::getLLVMPrimitive() {
    return &attribute;
}
