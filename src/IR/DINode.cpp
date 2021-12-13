#include "IR/IR.h"
#include "Util/Util.h"

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