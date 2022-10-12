#include "IR/index.h"
#include "Util/index.h"

void Attribute::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);

    Napi::Object attributeKinds = Napi::Object::New(env);
    attributeKinds.Set("AlwaysInline", Napi::Number::New(env, llvm::Attribute::AttrKind::AlwaysInline));
    attributeKinds.Set("ArgMemOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::ArgMemOnly));
    attributeKinds.Set("Builtin", Napi::Number::New(env, llvm::Attribute::AttrKind::Builtin));
    attributeKinds.Set("Cold", Napi::Number::New(env, llvm::Attribute::AttrKind::Cold));
    attributeKinds.Set("Convergent", Napi::Number::New(env, llvm::Attribute::AttrKind::Convergent));
    attributeKinds.Set("DisableSanitizerInstrumentation", Napi::Number::New(env, llvm::Attribute::AttrKind::DisableSanitizerInstrumentation));
    attributeKinds.Set("Hot", Napi::Number::New(env, llvm::Attribute::AttrKind::Hot));
    attributeKinds.Set("ImmArg", Napi::Number::New(env, llvm::Attribute::AttrKind::ImmArg));
    attributeKinds.Set("InReg", Napi::Number::New(env, llvm::Attribute::AttrKind::InReg));
    attributeKinds.Set("InaccessibleMemOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::InaccessibleMemOnly));
    attributeKinds.Set("InaccessibleMemOrArgMemOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::InaccessibleMemOrArgMemOnly));
    attributeKinds.Set("InlineHint", Napi::Number::New(env, llvm::Attribute::AttrKind::InlineHint));
    attributeKinds.Set("JumpTable", Napi::Number::New(env, llvm::Attribute::AttrKind::JumpTable));
    attributeKinds.Set("MinSize", Napi::Number::New(env, llvm::Attribute::AttrKind::MinSize));
    attributeKinds.Set("MustProgress", Napi::Number::New(env, llvm::Attribute::AttrKind::MustProgress));
    attributeKinds.Set("Naked", Napi::Number::New(env, llvm::Attribute::AttrKind::Naked));
    attributeKinds.Set("Nest", Napi::Number::New(env, llvm::Attribute::AttrKind::Nest));
    attributeKinds.Set("NoAlias", Napi::Number::New(env, llvm::Attribute::AttrKind::NoAlias));
    attributeKinds.Set("NoBuiltin", Napi::Number::New(env, llvm::Attribute::AttrKind::NoBuiltin));
    attributeKinds.Set("NoCallback", Napi::Number::New(env, llvm::Attribute::AttrKind::NoCallback));
    attributeKinds.Set("NoCapture", Napi::Number::New(env, llvm::Attribute::AttrKind::NoCapture));
    attributeKinds.Set("NoCfCheck", Napi::Number::New(env, llvm::Attribute::AttrKind::NoCfCheck));
    attributeKinds.Set("NoDuplicate", Napi::Number::New(env, llvm::Attribute::AttrKind::NoDuplicate));
    attributeKinds.Set("NoFree", Napi::Number::New(env, llvm::Attribute::AttrKind::NoFree));
    attributeKinds.Set("NoImplicitFloat", Napi::Number::New(env, llvm::Attribute::AttrKind::NoImplicitFloat));
    attributeKinds.Set("NoInline", Napi::Number::New(env, llvm::Attribute::AttrKind::NoInline));
    attributeKinds.Set("NoMerge", Napi::Number::New(env, llvm::Attribute::AttrKind::NoMerge));
    attributeKinds.Set("NoProfile", Napi::Number::New(env, llvm::Attribute::AttrKind::NoProfile));
    attributeKinds.Set("NoRecurse", Napi::Number::New(env, llvm::Attribute::AttrKind::NoRecurse));
    attributeKinds.Set("NoRedZone", Napi::Number::New(env, llvm::Attribute::AttrKind::NoRedZone));
    attributeKinds.Set("NoReturn", Napi::Number::New(env, llvm::Attribute::AttrKind::NoReturn));
    attributeKinds.Set("NoSanitizeCoverage", Napi::Number::New(env, llvm::Attribute::AttrKind::NoSanitizeCoverage));
    attributeKinds.Set("NoSync", Napi::Number::New(env, llvm::Attribute::AttrKind::NoSync));
    attributeKinds.Set("NoUndef", Napi::Number::New(env, llvm::Attribute::AttrKind::NoUndef));
    attributeKinds.Set("NoUnwind", Napi::Number::New(env, llvm::Attribute::AttrKind::NoUnwind));
    attributeKinds.Set("NonLazyBind", Napi::Number::New(env, llvm::Attribute::AttrKind::NonLazyBind));
    attributeKinds.Set("NonNull", Napi::Number::New(env, llvm::Attribute::AttrKind::NonNull));
    attributeKinds.Set("NullPointerIsValid", Napi::Number::New(env, llvm::Attribute::AttrKind::NullPointerIsValid));
    attributeKinds.Set("OptForFuzzing", Napi::Number::New(env, llvm::Attribute::AttrKind::OptForFuzzing));
    attributeKinds.Set("OptimizeForSize", Napi::Number::New(env, llvm::Attribute::AttrKind::OptimizeForSize));
    attributeKinds.Set("OptimizeNone", Napi::Number::New(env, llvm::Attribute::AttrKind::OptimizeNone));
    attributeKinds.Set("ReadNone", Napi::Number::New(env, llvm::Attribute::AttrKind::ReadNone));
    attributeKinds.Set("ReadOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::ReadOnly));
    attributeKinds.Set("Returned", Napi::Number::New(env, llvm::Attribute::AttrKind::Returned));
    attributeKinds.Set("ReturnsTwice", Napi::Number::New(env, llvm::Attribute::AttrKind::ReturnsTwice));
    attributeKinds.Set("SExt", Napi::Number::New(env, llvm::Attribute::AttrKind::SExt));
    attributeKinds.Set("SafeStack", Napi::Number::New(env, llvm::Attribute::AttrKind::SafeStack));
    attributeKinds.Set("SanitizeAddress", Napi::Number::New(env, llvm::Attribute::AttrKind::SanitizeAddress));
    attributeKinds.Set("SanitizeHWAddress", Napi::Number::New(env, llvm::Attribute::AttrKind::SanitizeHWAddress));
    attributeKinds.Set("SanitizeMemTag", Napi::Number::New(env, llvm::Attribute::AttrKind::SanitizeMemTag));
    attributeKinds.Set("SanitizeMemory", Napi::Number::New(env, llvm::Attribute::AttrKind::SanitizeMemory));
    attributeKinds.Set("SanitizeThread", Napi::Number::New(env, llvm::Attribute::AttrKind::SanitizeThread));
    attributeKinds.Set("ShadowCallStack", Napi::Number::New(env, llvm::Attribute::AttrKind::ShadowCallStack));
    attributeKinds.Set("Speculatable", Napi::Number::New(env, llvm::Attribute::AttrKind::Speculatable));
    attributeKinds.Set("SpeculativeLoadHardening", Napi::Number::New(env, llvm::Attribute::AttrKind::SpeculativeLoadHardening));
    attributeKinds.Set("StackProtect", Napi::Number::New(env, llvm::Attribute::AttrKind::StackProtect));
    attributeKinds.Set("StackProtectReq", Napi::Number::New(env, llvm::Attribute::AttrKind::StackProtectReq));
    attributeKinds.Set("StackProtectStrong", Napi::Number::New(env, llvm::Attribute::AttrKind::StackProtectStrong));
    attributeKinds.Set("StrictFP", Napi::Number::New(env, llvm::Attribute::AttrKind::StrictFP));
    attributeKinds.Set("SwiftAsync", Napi::Number::New(env, llvm::Attribute::AttrKind::SwiftAsync));
    attributeKinds.Set("SwiftError", Napi::Number::New(env, llvm::Attribute::AttrKind::SwiftError));
    attributeKinds.Set("SwiftSelf", Napi::Number::New(env, llvm::Attribute::AttrKind::SwiftSelf));
    attributeKinds.Set("UWTable", Napi::Number::New(env, llvm::Attribute::AttrKind::UWTable));
    attributeKinds.Set("WillReturn", Napi::Number::New(env, llvm::Attribute::AttrKind::WillReturn));
    attributeKinds.Set("WriteOnly", Napi::Number::New(env, llvm::Attribute::AttrKind::WriteOnly));
    attributeKinds.Set("LastEnumAttr", Napi::Number::New(env, llvm::Attribute::AttrKind::LastEnumAttr));
    attributeKinds.Set("ByRef", Napi::Number::New(env, llvm::Attribute::AttrKind::ByRef));
    attributeKinds.Set("ByVal", Napi::Number::New(env, llvm::Attribute::AttrKind::ByVal));
    attributeKinds.Set("ElementType", Napi::Number::New(env, llvm::Attribute::AttrKind::ElementType));
    attributeKinds.Set("InAlloca", Napi::Number::New(env, llvm::Attribute::AttrKind::InAlloca));
    attributeKinds.Set("Preallocated", Napi::Number::New(env, llvm::Attribute::AttrKind::Preallocated));
    attributeKinds.Set("LastTypeAttr", Napi::Number::New(env, llvm::Attribute::AttrKind::LastTypeAttr));
    attributeKinds.Set("Alignment", Napi::Number::New(env, llvm::Attribute::AttrKind::Alignment));
    attributeKinds.Set("AllocSize", Napi::Number::New(env, llvm::Attribute::AttrKind::AllocSize));
    attributeKinds.Set("Dereferenceable", Napi::Number::New(env, llvm::Attribute::AttrKind::Dereferenceable));
    attributeKinds.Set("DereferenceableOrNull", Napi::Number::New(env, llvm::Attribute::AttrKind::DereferenceableOrNull));
    attributeKinds.Set("StackAlignment", Napi::Number::New(env, llvm::Attribute::AttrKind::StackAlignment));
    attributeKinds.Set("VScaleRange", Napi::Number::New(env, llvm::Attribute::AttrKind::VScaleRange));

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
