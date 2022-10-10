#include "IR/index.h"
#include "Util/index.h"

void attribute::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object attributeNS = Napi::Object::New(env);

    Napi::Object attrKindNS = Napi::Object::New(env);
    attrKindNS.Set("ByVal", Napi::Number::New(env, llvm::Attribute::AttrKind::ByVal));
    attrKindNS.Set("InReg", Napi::Number::New(env, llvm::Attribute::AttrKind::InReg));
    attrKindNS.Set("NoAlias", Napi::Number::New(env, llvm::Attribute::AttrKind::NoAlias));
    attrKindNS.Set("NoInline", Napi::Number::New(env, llvm::Attribute::AttrKind::NoInline));
    attrKindNS.Set("NoUnwind", Napi::Number::New(env, llvm::Attribute::AttrKind::NoUnwind));
    attrKindNS.Set("ReadOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::ReadOnly));
    attrKindNS.Set("SExt", Napi::Number::New(env, llvm::Attribute::AttrKind::SExt));
    attrKindNS.Set("NoRecurse", Napi::Number::New(env, llvm::Attribute::AttrKind::NoRecurse));
    attrKindNS.Set("NonNull", Napi::Number::New(env, llvm::Attribute::AttrKind::NonNull));

    attributeNS.Set("AttrKind", attrKindNS);
    exports.Set("Attributes", attributeNS);
}

llvm::Attribute::AttrKind attribute::Extract(const Napi::Value &value) {
    return static_cast<llvm::Attribute::AttrKind>((unsigned)value.As<Napi::Number>());
}
