#include "IR/index.h"
#include "Util/index.h"

void Attribute::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);

    Napi::Object attributeKinds = Napi::Object::New(env);

#define GET_ATTR_NAMES
#define ATTRIBUTE_ENUM(EnumName, lower) attributeKinds.Set(#EnumName, Napi::Number::New(env, llvm::Attribute::AttrKind::EnumName));
#include "llvm/IR/Attributes.inc"

    Napi::Function func = DefineClass(env, "Attribute", {
            StaticValue("AttrKind", attributeKinds),
            StaticMethod("get", &Attribute::get)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Attribute", func);
}

Napi::Object Attribute::New(Napi::Env env, llvm::AttributeImpl *_attrImpl) {
    return constructor.New({Napi::External<llvm::AttributeImpl>::New(env, _attrImpl)});
}

bool Attribute::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Attribute Attribute::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Attribute::Attribute(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();

    if (argsLen == 1 && info[0].IsExternal()) {
        auto external = info[0].As<Napi::External<llvm::AttributeImpl>>();
        attrImpl = external.Data();
    } else {
        throw Napi::TypeError::New(env, ErrMsg::Class::Attribute::constructor);
    }
}

llvm::Attribute Attribute::getLLVMPrimitive() {
    return llvm::Attribute::fromRawPointer(attrImpl);
}

Napi::Value Attribute::get(const Napi::CallbackInfo &info) {
    auto env = info.Env();
    unsigned argsLen = info.Length();
    bool isMatch = false;
    llvm::Attribute attribute;
    if (argsLen >= 2 && argsLen <= 3 && LLVMContext::IsClassOf(info[0])) {
        llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
        if (info[1].IsNumber()) {
            unsigned rawAttrKind = info[1].As<Napi::Number>();
            if (rawAttrKind < llvm::Attribute::AttrKind::FirstEnumAttr ||
                rawAttrKind > llvm::Attribute::AttrKind::LastEnumAttr) {
                throw Napi::TypeError::New(env, ErrMsg::Class::Attribute::invalidAttrKind);
            }
            auto attrKind = static_cast<llvm::Attribute::AttrKind>(rawAttrKind);
            if (argsLen == 2) {
                isMatch = true;
                attribute = llvm::Attribute::get(context, attrKind);
            } else if (argsLen == 3) {
                if (info[2].IsNumber()) {
                    isMatch = true;
                    uint64_t value = info[2].As<Napi::Number>().Int64Value();
                    attribute = llvm::Attribute::get(context, attrKind, value);
                } else if (Type::IsClassOf(info[2])) {
                    isMatch = true;
                    llvm::Type *type = Type::Extract(info[2]);
                    attribute = llvm::Attribute::get(context, attrKind, type);
                }
            }
        } else if (info[1].IsString()) {
            std::string attrKind = info[1].As<Napi::String>();
            if (argsLen == 2) {
                isMatch = true;
                attribute = llvm::Attribute::get(context, attrKind);
            } else if (argsLen == 3 && info[2].IsString()) {
                isMatch = true;
                std::string value = info[2].As<Napi::String>();
                attribute = llvm::Attribute::get(context, attrKind, value);
            }
        }
    }
    if (!isMatch) {
        throw Napi::TypeError::New(env, ErrMsg::Class::Attribute::get);
    }

    return Attribute::New(env, static_cast<llvm::AttributeImpl *>(attribute.getRawPointer()));
}