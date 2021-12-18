#include "BinaryFormat/Dwarf.h"

void dwarf::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object dwarfNS = Napi::Object::New(env);

    Napi::Object constantsNS = Napi::Object::New(env);
    constantsNS.Set("DWARF_VERSION", Napi::Number::New(env, llvm::dwarf::LLVMConstants::DWARF_VERSION));

    Napi::Object typeKindNS = Napi::Object::New(env);
    typeKindNS.Set("DW_ATE_address", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_address));
    typeKindNS.Set("DW_ATE_boolean", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_boolean));
    typeKindNS.Set("DW_ATE_complex_float", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_complex_float));
    typeKindNS.Set("DW_ATE_float", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_float));
    typeKindNS.Set("DW_ATE_signed", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_signed));
    typeKindNS.Set("DW_ATE_signed_char", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_signed_char));
    typeKindNS.Set("DW_ATE_unsigned", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_unsigned));
    typeKindNS.Set("DW_ATE_unsigned_char", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_unsigned_char));
    typeKindNS.Set("DW_ATE_imaginary_float", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_imaginary_float));
    typeKindNS.Set("DW_ATE_packed_decimal", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_packed_decimal));
    typeKindNS.Set("DW_ATE_numeric_string", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_numeric_string));
    typeKindNS.Set("DW_ATE_edited", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_edited));
    typeKindNS.Set("DW_ATE_signed_fixed", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_signed_fixed));
    typeKindNS.Set("DW_ATE_unsigned_fixed", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_unsigned_fixed));
    typeKindNS.Set("DW_ATE_decimal_float", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_decimal_float));
    typeKindNS.Set("DW_ATE_UTF", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_UTF));
    typeKindNS.Set("DW_ATE_UCS", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_UCS));
    typeKindNS.Set("DW_ATE_ASCII", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_ASCII));
    typeKindNS.Set("DW_ATE_lo_user", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_lo_user));
    typeKindNS.Set("DW_ATE_hi_user", Napi::Number::New(env, llvm::dwarf::TypeKind::DW_ATE_hi_user));

    Napi::Object sourceLanguageNS = Napi::Object::New(env);
    sourceLanguageNS.Set("DW_LANG_C89", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C89));
    sourceLanguageNS.Set("DW_LANG_C", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C));
    sourceLanguageNS.Set("DW_LANG_Ada83", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Ada83));
    sourceLanguageNS.Set("DW_LANG_C_plus_plus", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C_plus_plus));
    sourceLanguageNS.Set("DW_LANG_Cobol74", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Cobol74));
    sourceLanguageNS.Set("DW_LANG_Cobol85", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Cobol85));
    sourceLanguageNS.Set("DW_LANG_Fortran77", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Fortran77));
    sourceLanguageNS.Set("DW_LANG_Fortran90", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Fortran90));
    sourceLanguageNS.Set("DW_LANG_Pascal83", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Pascal83));
    sourceLanguageNS.Set("DW_LANG_Modula2", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Modula2));
    sourceLanguageNS.Set("DW_LANG_Java", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Java));
    sourceLanguageNS.Set("DW_LANG_C99", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C99));
    sourceLanguageNS.Set("DW_LANG_Ada95", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Ada95));
    sourceLanguageNS.Set("DW_LANG_Fortran95", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Fortran95));
    sourceLanguageNS.Set("DW_LANG_PLI", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_PLI));
    sourceLanguageNS.Set("DW_LANG_ObjC", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_ObjC));
    sourceLanguageNS.Set("DW_LANG_ObjC_plus_plus", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_ObjC_plus_plus));
    sourceLanguageNS.Set("DW_LANG_UPC", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_UPC));
    sourceLanguageNS.Set("DW_LANG_D", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_D));
    sourceLanguageNS.Set("DW_LANG_Python", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Python));
    sourceLanguageNS.Set("DW_LANG_OpenCL", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_OpenCL));
    sourceLanguageNS.Set("DW_LANG_Go", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Go));
    sourceLanguageNS.Set("DW_LANG_Modula3", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Modula3));
    sourceLanguageNS.Set("DW_LANG_Haskell", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Haskell));
    sourceLanguageNS.Set("DW_LANG_C_plus_plus_03", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C_plus_plus_03));
    sourceLanguageNS.Set("DW_LANG_C_plus_plus_11", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C_plus_plus_11));
    sourceLanguageNS.Set("DW_LANG_OCaml", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_OCaml));
    sourceLanguageNS.Set("DW_LANG_Rust", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Rust));
    sourceLanguageNS.Set("DW_LANG_C11", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C11));
    sourceLanguageNS.Set("DW_LANG_Swift", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Swift));
    sourceLanguageNS.Set("DW_LANG_Julia", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Julia));
    sourceLanguageNS.Set("DW_LANG_Dylan", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Dylan));
    sourceLanguageNS.Set("DW_LANG_C_plus_plus_14", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_C_plus_plus_14));
    sourceLanguageNS.Set("DW_LANG_Fortran03", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Fortran03));
    sourceLanguageNS.Set("DW_LANG_Fortran08", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_Fortran08));
    sourceLanguageNS.Set("DW_LANG_RenderScript", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_RenderScript));
    sourceLanguageNS.Set("DW_LANG_BLISS", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_BLISS));
    sourceLanguageNS.Set("DW_LANG_lo_user", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_lo_user));
    sourceLanguageNS.Set("DW_LANG_hi_user", Napi::Number::New(env, llvm::dwarf::SourceLanguage::DW_LANG_hi_user));

    dwarfNS.Set("LLVMConstants", constantsNS);
    dwarfNS.Set("TypeKind", typeKindNS);
    dwarfNS.Set("SourceLanguage", sourceLanguageNS);
    exports.Set("dwarf", dwarfNS);
}
