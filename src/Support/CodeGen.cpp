#include "Support/index.h"

#include <llvm/Support/CodeGen.h>

#define SET_ENUM_VALUE_NUM(obj, en, name) \
    obj.Set(#name, Napi::Number::New(env, en::name))

#define SET_NAME_ENUM_VALUE_NUM(obj, prop, en, name) \
    obj.Set(#prop, Napi::Number::New(env, en::name))

void initReloc(Napi::Env env, Napi::Object &exports) {
    Napi::Object relocNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, Static);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, Static);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, PIC_);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, DynamicNoPIC);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, ROPI);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, RWPI);
    SET_ENUM_VALUE_NUM(relocNS, llvm::Reloc, ROPI_RWPI);
    exports.Set("Reloc", relocNS);
}

void initCodeModel(Napi::Env env, Napi::Object &exports) {
    Napi::Object codeModelNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(codeModelNS, llvm::CodeModel, Tiny);
    SET_ENUM_VALUE_NUM(codeModelNS, llvm::CodeModel, Small);
    SET_ENUM_VALUE_NUM(codeModelNS, llvm::CodeModel, Kernel);
    SET_ENUM_VALUE_NUM(codeModelNS, llvm::CodeModel, Medium);
    SET_ENUM_VALUE_NUM(codeModelNS, llvm::CodeModel, Large);
    exports.Set("CodeModel", codeModelNS);
}

void initPICLevel(Napi::Env env, Napi::Object &exports) {
    Napi::Object picLevelNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(picLevelNS, llvm::PICLevel, NotPIC);
    SET_ENUM_VALUE_NUM(picLevelNS, llvm::PICLevel, SmallPIC);
    SET_ENUM_VALUE_NUM(picLevelNS, llvm::PICLevel, BigPIC);
    exports.Set("PICLevel", picLevelNS);
}

void initPIELevel(Napi::Env env, Napi::Object &exports) {
    Napi::Object pieLevelNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(pieLevelNS, llvm::PIELevel, Default);
    SET_ENUM_VALUE_NUM(pieLevelNS, llvm::PIELevel, Small);
    SET_ENUM_VALUE_NUM(pieLevelNS, llvm::PIELevel, Large);
    exports.Set("PIELevel", pieLevelNS);
}

void initTLSModel(Napi::Env env, Napi::Object &exports) {
    Napi::Object tlsModelNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(tlsModelNS, llvm::TLSModel, GeneralDynamic);
    SET_ENUM_VALUE_NUM(tlsModelNS, llvm::TLSModel, LocalDynamic);
    SET_ENUM_VALUE_NUM(tlsModelNS, llvm::TLSModel, InitialExec);
    SET_ENUM_VALUE_NUM(tlsModelNS, llvm::TLSModel, LocalExec);
    exports.Set("TLSModel", tlsModelNS);
}

void initCodeGenOpt(Napi::Env env, Napi::Object &exports) {
    Napi::Object codeGenOptNS = Napi::Object::New(env);
    SET_ENUM_VALUE_NUM(codeGenOptNS, llvm::CodeGenOpt, None);
    SET_ENUM_VALUE_NUM(codeGenOptNS, llvm::CodeGenOpt, Less);
    SET_ENUM_VALUE_NUM(codeGenOptNS, llvm::CodeGenOpt, Default);
    SET_ENUM_VALUE_NUM(codeGenOptNS, llvm::CodeGenOpt, Aggressive);
    exports.Set("CodeGenOpt", codeGenOptNS);
}

void initCodeGenFileType(Napi::Env env, Napi::Object &exports) {
    Napi::Object codeGenFileTypeNS = Napi::Object::New(env);
    SET_NAME_ENUM_VALUE_NUM(codeGenFileTypeNS, Assembly, llvm::CodeGenFileType, CGFT_AssemblyFile);
    SET_NAME_ENUM_VALUE_NUM(codeGenFileTypeNS, Object, llvm::CodeGenFileType, CGFT_ObjectFile);
    SET_NAME_ENUM_VALUE_NUM(codeGenFileTypeNS, Null, llvm::CodeGenFileType, CGFT_Null);
    exports.Set("CodeGenFileType", codeGenFileTypeNS);
}

void CodeGen::Init(Napi::Env env, Napi::Object &exports) {
    initReloc(env, exports);
    initCodeModel(env, exports);
    initPICLevel(env, exports);
    initPIELevel(env, exports);
    initTLSModel(env, exports);
    initCodeGenOpt(env, exports);
    initCodeGenFileType(env, exports);
}

#undef SET_ENUM_VALUE_NUM
#undef SET_NAME_ENUM_VALUE_NUM
