#include "IR/index.h"
#include "Util/index.h"

//===----------------------------------------------------------------------===//
// class DITypeRefArray
//===----------------------------------------------------------------------===//

void DITypeRefArray::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DITypeRefArray", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("DITypeRefArray", func);
}

Napi::Value DITypeRefArray::New(Napi::Env env, llvm::DITypeRefArray *array) {
    return constructor.New({Napi::External<llvm::DITypeRefArray>::New(env, array)});
}

bool DITypeRefArray::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DITypeRefArray *DITypeRefArray::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DITypeRefArray::DITypeRefArray(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DITypeRefArray::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DITypeRefArray>>();
    array = external.Data();
}

llvm::DITypeRefArray *DITypeRefArray::getLLVMPrimitive() {
    return array;
}

//===----------------------------------------------------------------------===//
// class DINode
//===----------------------------------------------------------------------===//

void DINode::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);

    Napi::Object diFlagsNS = Napi::Object::New(env);
    diFlagsNS.Set("FlagZero", Napi::Number::New(env, llvm::DINode::DIFlags::FlagZero));
    diFlagsNS.Set("FlagPrivate", Napi::Number::New(env, llvm::DINode::DIFlags::FlagPrivate));
    diFlagsNS.Set("FlagProtected", Napi::Number::New(env, llvm::DINode::DIFlags::FlagProtected));
    diFlagsNS.Set("FlagPublic", Napi::Number::New(env, llvm::DINode::DIFlags::FlagPublic));
    diFlagsNS.Set("FlagFwdDecl", Napi::Number::New(env, llvm::DINode::DIFlags::FlagFwdDecl));
    diFlagsNS.Set("FlagAppleBlock", Napi::Number::New(env, llvm::DINode::DIFlags::FlagAppleBlock));
    diFlagsNS.Set("FlagReservedBit4", Napi::Number::New(env, llvm::DINode::DIFlags::FlagReservedBit4));
    diFlagsNS.Set("FlagVirtual", Napi::Number::New(env, llvm::DINode::DIFlags::FlagVirtual));
    diFlagsNS.Set("FlagArtificial", Napi::Number::New(env, llvm::DINode::DIFlags::FlagArtificial));
    diFlagsNS.Set("FlagExplicit", Napi::Number::New(env, llvm::DINode::DIFlags::FlagExplicit));
    diFlagsNS.Set("FlagPrototyped", Napi::Number::New(env, llvm::DINode::DIFlags::FlagPrototyped));
    diFlagsNS.Set("FlagObjcClassComplete", Napi::Number::New(env, llvm::DINode::DIFlags::FlagObjcClassComplete));
    diFlagsNS.Set("FlagObjectPointer", Napi::Number::New(env, llvm::DINode::DIFlags::FlagObjectPointer));
    diFlagsNS.Set("FlagVector", Napi::Number::New(env, llvm::DINode::DIFlags::FlagVector));
    diFlagsNS.Set("FlagStaticMember", Napi::Number::New(env, llvm::DINode::DIFlags::FlagStaticMember));
    diFlagsNS.Set("FlagLValueReference", Napi::Number::New(env, llvm::DINode::DIFlags::FlagLValueReference));
    diFlagsNS.Set("FlagRValueReference", Napi::Number::New(env, llvm::DINode::DIFlags::FlagRValueReference));
    diFlagsNS.Set("FlagExportSymbols", Napi::Number::New(env, llvm::DINode::DIFlags::FlagExportSymbols));
    diFlagsNS.Set("FlagSingleInheritance", Napi::Number::New(env, llvm::DINode::DIFlags::FlagSingleInheritance));
    diFlagsNS.Set("FlagMultipleInheritance", Napi::Number::New(env, llvm::DINode::DIFlags::FlagMultipleInheritance));
    diFlagsNS.Set("FlagVirtualInheritance", Napi::Number::New(env, llvm::DINode::DIFlags::FlagVirtualInheritance));
    diFlagsNS.Set("FlagIntroducedVirtual", Napi::Number::New(env, llvm::DINode::DIFlags::FlagIntroducedVirtual));
    diFlagsNS.Set("FlagBitField", Napi::Number::New(env, llvm::DINode::DIFlags::FlagBitField));
    diFlagsNS.Set("FlagNoReturn", Napi::Number::New(env, llvm::DINode::DIFlags::FlagNoReturn));
    diFlagsNS.Set("FlagTypePassByValue", Napi::Number::New(env, llvm::DINode::DIFlags::FlagTypePassByValue));
    diFlagsNS.Set("FlagTypePassByReference", Napi::Number::New(env, llvm::DINode::DIFlags::FlagTypePassByReference));
    diFlagsNS.Set("FlagEnumClass", Napi::Number::New(env, llvm::DINode::DIFlags::FlagEnumClass));
    diFlagsNS.Set("FlagThunk", Napi::Number::New(env, llvm::DINode::DIFlags::FlagThunk));
    diFlagsNS.Set("FlagNonTrivial", Napi::Number::New(env, llvm::DINode::DIFlags::FlagNonTrivial));
    diFlagsNS.Set("FlagBigEndian", Napi::Number::New(env, llvm::DINode::DIFlags::FlagBigEndian));
    diFlagsNS.Set("FlagLittleEndian", Napi::Number::New(env, llvm::DINode::DIFlags::FlagLittleEndian));
    diFlagsNS.Set("FlagAllCallsDescribed", Napi::Number::New(env, llvm::DINode::DIFlags::FlagAllCallsDescribed));
    diFlagsNS.Set("FlagIndirectVirtualBase", Napi::Number::New(env, llvm::DINode::DIFlags::FlagIndirectVirtualBase));
    diFlagsNS.Set("FlagAccessibility", Napi::Number::New(env, llvm::DINode::DIFlags::FlagAccessibility));
    diFlagsNS.Set("FlagPtrToMemberRep", Napi::Number::New(env, llvm::DINode::DIFlags::FlagPtrToMemberRep));

    Napi::Object diSPFlagsNS = Napi::Object::New(env);
    diSPFlagsNS.Set("SPFlagZero", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagZero));
    diSPFlagsNS.Set("SPFlagVirtual", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagVirtual));
    diSPFlagsNS.Set("SPFlagPureVirtual", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagPureVirtual));
    diSPFlagsNS.Set("SPFlagLocalToUnit", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagLocalToUnit));
    diSPFlagsNS.Set("SPFlagDefinition", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagDefinition));
    diSPFlagsNS.Set("SPFlagOptimized", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagOptimized));
    diSPFlagsNS.Set("SPFlagPure", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagPure));
    diSPFlagsNS.Set("SPFlagElemental", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagElemental));
    diSPFlagsNS.Set("SPFlagRecursive", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagRecursive));
    diSPFlagsNS.Set("SPFlagMainSubprogram", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagMainSubprogram));
    diSPFlagsNS.Set("SPFlagDeleted", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagDeleted));
    diSPFlagsNS.Set("SPFlagObjCDirect", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagObjCDirect));
    diSPFlagsNS.Set("SPFlagNonvirtual", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagNonvirtual));
    diSPFlagsNS.Set("SPFlagVirtuality", Napi::Number::New(env, llvm::DISubprogram::DISPFlags::SPFlagVirtuality));

    Napi::Function func = DefineClass(env, "DINode", {
            StaticValue("DIFlags", diFlagsNS),
            StaticValue("DISPFlags", diSPFlagsNS),
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DINode", func);
}

Napi::Value DINode::New(Napi::Env env, llvm::DINode *node) {
    if (llvm::isa<llvm::DIScope>(node)) {
        return DIScope::New(env, llvm::cast<llvm::DIScope>(node));
    } else if (llvm::isa<llvm::DIVariable>(node)) {
        return DIVariable::New(env, llvm::cast<llvm::DIVariable>(node));
    }
    return constructor.New({Napi::External<llvm::DINode>::New(env, node)});
}

bool DINode::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DINode *DINode::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DINode::DINode(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DINode::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DINode>>();
    node = external.Data();
}

llvm::DINode *DINode::getLLVMPrimitive() {
    return node;
}

//===----------------------------------------------------------------------===//
// class DIScope
//===----------------------------------------------------------------------===//

void DIScope::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIScope", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DINode::constructor.Value());
    exports.Set("DIScope", func);
}

Napi::Value DIScope::New(Napi::Env env, llvm::DIScope *scope) {
    if (llvm::isa<llvm::DIFile>(scope)) {
        return DIFile::New(env, llvm::cast<llvm::DIFile>(scope));
    } else if (llvm::isa<llvm::DIType>(scope)) {
        return DIType::New(env, llvm::cast<llvm::DIType>(scope));
    } else if (llvm::isa<llvm::DICompileUnit>(scope)) {
        return DICompileUnit::New(env, llvm::cast<llvm::DICompileUnit>(scope));
    } else if (llvm::isa<llvm::DILocalScope>(scope)) {
        return DILocalScope::New(env, llvm::cast<llvm::DILocalScope>(scope));
    } else if (llvm::isa<llvm::DINamespace>(scope)) {
        return DINamespace::New(env, llvm::cast<llvm::DINamespace>(scope));
    }
    return constructor.New({Napi::External<llvm::DIScope>::New(env, scope)});
}

bool DIScope::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIScope *DIScope::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIScope::DIScope(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIScope::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIScope>>();
    scope = external.Data();
}

llvm::DIScope *DIScope::getLLVMPrimitive() {
    return scope;
}

//===----------------------------------------------------------------------===//
// class DIFile
//===----------------------------------------------------------------------===//

void DIFile::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIFile", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DIFile", func);
}

Napi::Value DIFile::New(Napi::Env env, llvm::DIFile *file) {
    return constructor.New({Napi::External<llvm::DIFile>::New(env, file)});
}

bool DIFile::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIFile *DIFile::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIFile::DIFile(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIFile::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIFile>>();
    file = external.Data();
}

llvm::DIFile *DIFile::getLLVMPrimitive() {
    return file;
}

//===----------------------------------------------------------------------===//
// class DIType
//===----------------------------------------------------------------------===//

void DIType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DIType", func);
}

Napi::Value DIType::New(Napi::Env env, llvm::DIType *type) {
    if (llvm::isa<llvm::DIBasicType>(type)) {
        return DIBasicType::New(env, llvm::cast<llvm::DIBasicType>(type));
    } else if (llvm::isa<llvm::DIDerivedType>(type)) {
        return DIDerivedType::New(env, llvm::cast<llvm::DIDerivedType>(type));
    } else if (llvm::isa<llvm::DICompositeType>(type)) {
        return DICompositeType::New(env, llvm::cast<llvm::DICompositeType>(type));
    } else if (llvm::isa<llvm::DISubroutineType>(type)) {
        return DISubroutineType::New(env, llvm::cast<llvm::DISubroutineType>(type));
    }
    return constructor.New({Napi::External<llvm::DIType>::New(env, type)});
}

bool DIType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIType *DIType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIType::DIType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIType>>();
    type = external.Data();
}

llvm::DIType *DIType::getLLVMPrimitive() {
    return type;
}

//===----------------------------------------------------------------------===//
// class DIBasicType
//===----------------------------------------------------------------------===//

void DIBasicType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIBasicType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DIBasicType", func);
}

Napi::Value DIBasicType::New(Napi::Env env, llvm::DIBasicType *type) {
    return constructor.New({Napi::External<llvm::DIBasicType>::New(env, type)});
}

bool DIBasicType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIBasicType *DIBasicType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIBasicType::DIBasicType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIBasicType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIBasicType>>();
    type = external.Data();
}

llvm::DIBasicType *DIBasicType::getLLVMPrimitive() {
    return type;
}

//===----------------------------------------------------------------------===//
// class DIDerivedType
//===----------------------------------------------------------------------===//

void DIDerivedType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIDerivedType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DIDerivedType", func);
}

Napi::Value DIDerivedType::New(Napi::Env env, llvm::DIDerivedType *type) {
    return constructor.New({Napi::External<llvm::DIDerivedType>::New(env, type)});
}

bool DIDerivedType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIDerivedType *DIDerivedType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIDerivedType::DIDerivedType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIDerivedType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIDerivedType>>();
    type = external.Data();
}

llvm::DIDerivedType *DIDerivedType::getLLVMPrimitive() {
    return type;
}

//===----------------------------------------------------------------------===//
// class DICompositeType
//===----------------------------------------------------------------------===//

void DICompositeType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DICompositeType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DICompositeType", func);
}

Napi::Value DICompositeType::New(Napi::Env env, llvm::DICompositeType *type) {
    return constructor.New({Napi::External<llvm::DICompositeType>::New(env, type)});
}

bool DICompositeType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DICompositeType *DICompositeType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DICompositeType::DICompositeType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DICompositeType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DICompositeType>>();
    type = external.Data();
}

llvm::DICompositeType *DICompositeType::getLLVMPrimitive() {
    return type;
}

//===----------------------------------------------------------------------===//
// class DISubroutineType
//===----------------------------------------------------------------------===//

void DISubroutineType::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DISubroutineType", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIType::constructor.Value());
    exports.Set("DISubroutineType", func);
}

Napi::Value DISubroutineType::New(Napi::Env env, llvm::DISubroutineType *type) {
    return constructor.New({Napi::External<llvm::DISubroutineType>::New(env, type)});
}

bool DISubroutineType::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DISubroutineType *DISubroutineType::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DISubroutineType::DISubroutineType(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DISubroutineType::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DISubroutineType>>();
    type = external.Data();
}

llvm::DISubroutineType *DISubroutineType::getLLVMPrimitive() {
    return type;
}

//===----------------------------------------------------------------------===//
// class DICompileUnit
//===----------------------------------------------------------------------===//

void DICompileUnit::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DICompileUnit", {
            InstanceMethod("getFile", &DICompileUnit::getFile)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DICompileUnit", func);
}

Napi::Value DICompileUnit::New(Napi::Env env, llvm::DICompileUnit *unit) {
    return constructor.New({Napi::External<llvm::DICompileUnit>::New(env, unit)});
}

bool DICompileUnit::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DICompileUnit *DICompileUnit::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DICompileUnit::DICompileUnit(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DICompileUnit::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DICompileUnit>>();
    unit = external.Data();
}

llvm::DICompileUnit *DICompileUnit::getLLVMPrimitive() {
    return unit;
}

Napi::Value DICompileUnit::getFile(const Napi::CallbackInfo &info) {
    return DIFile::New(info.Env(), unit->getFile());
}

//===----------------------------------------------------------------------===//
// class DILocalScope
//===----------------------------------------------------------------------===//

void DILocalScope::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DILocalScope", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DILocalScope", func);
}

Napi::Value DILocalScope::New(Napi::Env env, llvm::DILocalScope *scope) {
    if (llvm::isa<llvm::DILexicalBlock>(scope)) {
        return DILexicalBlock::New(env, llvm::cast<llvm::DILexicalBlock>(scope));
    } else if (llvm::isa<llvm::DISubprogram>(scope)) {
        return DISubprogram::New(env, llvm::cast<llvm::DISubprogram>(scope));
    }
    return constructor.New({Napi::External<llvm::DILocalScope>::New(env, scope)});
}

bool DILocalScope::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILocalScope *DILocalScope::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILocalScope::DILocalScope(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILocalScope::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILocalScope>>();
    scope = external.Data();
}

llvm::DILocalScope *DILocalScope::getLLVMPrimitive() {
    return scope;
}

//===----------------------------------------------------------------------===//
// class DILocation
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
// class DISubprogram
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
// class DILexicalBlock
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
// class DINamespace
//===----------------------------------------------------------------------===//

void DINamespace::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DINamespace", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIScope::constructor.Value());
    exports.Set("DINamespace", func);
}

Napi::Value DINamespace::New(Napi::Env env, llvm::DINamespace *ns) {
    return constructor.New({Napi::External<llvm::DINamespace>::New(env, ns)});
}

bool DINamespace::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DINamespace *DINamespace::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DINamespace::DINamespace(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DINamespace::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DINamespace>>();
    ns = external.Data();
}

llvm::DINamespace *DINamespace::getLLVMPrimitive() {
    return ns;
}

//===----------------------------------------------------------------------===//
// class DIVariable
//===----------------------------------------------------------------------===//

void DIVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DINode::constructor.Value());
    exports.Set("DIVariable", func);
}

Napi::Value DIVariable::New(Napi::Env env, llvm::DIVariable *variable) {
    if (llvm::isa<llvm::DILocalVariable>(variable)) {
        return DILocalVariable::New(env, llvm::cast<llvm::DILocalVariable>(variable));
    } else if (llvm::isa<llvm::DIGlobalVariable>(variable)) {
        return DIGlobalVariable::New(env, llvm::cast<llvm::DIGlobalVariable>(variable));
    }
    return constructor.New({Napi::External<llvm::DIVariable>::New(env, variable)});
}

bool DIVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIVariable *DIVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIVariable::DIVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIVariable>>();
    variable = external.Data();
}

llvm::DIVariable *DIVariable::getLLVMPrimitive() {
    return variable;
}

//===----------------------------------------------------------------------===//
// class DIExpression
//===----------------------------------------------------------------------===//

void DIExpression::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIExpression", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DIExpression", func);
}

Napi::Value DIExpression::New(Napi::Env env, llvm::DIExpression *expression) {
    return constructor.New({Napi::External<llvm::DIExpression>::New(env, expression)});
}

bool DIExpression::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIExpression *DIExpression::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIExpression::DIExpression(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIExpression::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIExpression>>();
    expression = external.Data();
}

llvm::DIExpression *DIExpression::getLLVMPrimitive() {
    return expression;
}

//===----------------------------------------------------------------------===//
// class DIGlobalVariable
//===----------------------------------------------------------------------===//

void DIGlobalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIGlobalVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIVariable::constructor.Value());
    exports.Set("DIGlobalVariable", func);
}

Napi::Value DIGlobalVariable::New(Napi::Env env, llvm::DIGlobalVariable *variable) {
    return constructor.New({Napi::External<llvm::DIGlobalVariable>::New(env, variable)});
}

bool DIGlobalVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIGlobalVariable *DIGlobalVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIGlobalVariable::DIGlobalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIGlobalVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIGlobalVariable>>();
    variable = external.Data();
}

llvm::DIGlobalVariable *DIGlobalVariable::getLLVMPrimitive() {
    return variable;
}

//===----------------------------------------------------------------------===//
// class DILocalVariable
//===----------------------------------------------------------------------===//

void DILocalVariable::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DILocalVariable", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), DIVariable::constructor.Value());
    exports.Set("DILocalVariable", func);
}

Napi::Value DILocalVariable::New(Napi::Env env, llvm::DILocalVariable *variable) {
    return constructor.New({Napi::External<llvm::DILocalVariable>::New(env, variable)});
}

bool DILocalVariable::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DILocalVariable *DILocalVariable::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DILocalVariable::DILocalVariable(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DILocalVariable::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DILocalVariable>>();
    variable = external.Data();
}

llvm::DILocalVariable *DILocalVariable::getLLVMPrimitive() {
    return variable;
}

//===----------------------------------------------------------------------===//
// class DIGlobalVariableExpression
//===----------------------------------------------------------------------===//

void DIGlobalVariableExpression::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIGlobalVariableExpression", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    Inherit(env, constructor.Value(), MDNode::constructor.Value());
    exports.Set("DIGlobalVariableExpression", func);
}

Napi::Value DIGlobalVariableExpression::New(Napi::Env env, llvm::DIGlobalVariableExpression *expression) {
    return constructor.New({Napi::External<llvm::DIGlobalVariableExpression>::New(env, expression)});
}

bool DIGlobalVariableExpression::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIGlobalVariableExpression *DIGlobalVariableExpression::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIGlobalVariableExpression::DIGlobalVariableExpression(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !info[0].IsExternal()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::DIGlobalVariableExpression::constructor);
    }
    auto external = info[0].As<Napi::External<llvm::DIGlobalVariableExpression>>();
    expression = external.Data();
}

llvm::DIGlobalVariableExpression *DIGlobalVariableExpression::getLLVMPrimitive() {
    return expression;
}
