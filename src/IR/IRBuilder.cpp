#include "IR/index.h"
#include "ADT/APInt.h"
#include "Util/index.h"

using WrappedValue = Value;

void IRBuilder::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IRBuilder", {
            //===--------------------------------------------------------------------===//
            // Builder configuration methods
            //===--------------------------------------------------------------------===//

            InstanceMethod("ClearInsertionPoint", &IRBuilder::ClearInsertionPoint),
            InstanceMethod("GetInsertBlock", &IRBuilder::GetInsertBlock),
            InstanceMethod("SetInsertPoint", &IRBuilder::SetInsertPoint),
            InstanceMethod("SetCurrentDebugLocation", &IRBuilder::SetCurrentDebugLocation),

            StaticValue("InsertPoint", InsertPoint::Init(env, exports)),
            InstanceMethod("saveIP", &IRBuilder::saveIP),
            InstanceMethod("saveAndClearIP", &IRBuilder::saveAndClearIP),
            InstanceMethod("restoreIP", &IRBuilder::restoreIP),

            //===--------------------------------------------------------------------===//
            // Miscellaneous creation methods.
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateGlobalString", &IRBuilder::CreateGlobalString),
            InstanceMethod("getInt1", &IRBuilder::getInt1),
            InstanceMethod("getTrue", &IRBuilder::getBoolFactory<&LLVMIRBuilder::getTrue>),
            InstanceMethod("getFalse", &IRBuilder::getBoolFactory<&LLVMIRBuilder::getFalse>),
            InstanceMethod("getInt8", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt8>),
            InstanceMethod("getInt16", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt16>),
            InstanceMethod("getInt32", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt32>),
            InstanceMethod("getInt64", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt64>),
            InstanceMethod("getIntN", &IRBuilder::getIntN),
            InstanceMethod("getInt", &IRBuilder::getInt),

            //===--------------------------------------------------------------------===//
            // Type creation methods
            //===--------------------------------------------------------------------===//

            InstanceMethod("getInt1Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt1Ty>),
            InstanceMethod("getInt8Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt8Ty>),
            InstanceMethod("getInt16Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt16Ty>),
            InstanceMethod("getInt32Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt32Ty>),
            InstanceMethod("getInt64Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt64Ty>),
            InstanceMethod("getInt128Ty", &IRBuilder::getIntTypeFactory<&LLVMIRBuilder::getInt128Ty>),
            InstanceMethod("getIntNTy", &IRBuilder::getIntNTy),
            InstanceMethod("getHalfTy", &IRBuilder::getTypeFactory<&LLVMIRBuilder::getHalfTy>),
            InstanceMethod("getBFloatTy", &IRBuilder::getTypeFactory<&LLVMIRBuilder::getBFloatTy>),
            InstanceMethod("getFloatTy", &IRBuilder::getTypeFactory<&LLVMIRBuilder::getFloatTy>),
            InstanceMethod("getDoubleTy", &IRBuilder::getTypeFactory<&LLVMIRBuilder::getDoubleTy>),
            InstanceMethod("getVoidTy", &IRBuilder::getTypeFactory<&LLVMIRBuilder::getVoidTy>),
            InstanceMethod("getInt8PtrTy", &IRBuilder::getInt8PtrTy),
            InstanceMethod("getIntPtrTy", &IRBuilder::getIntPtrTy),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Terminators
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateRetVoid", &IRBuilder::CreateRetVoid),
            InstanceMethod("CreateRet", &IRBuilder::CreateRet),
            InstanceMethod("CreateBr", &IRBuilder::CreateBr),
            InstanceMethod("CreateCondBr", &IRBuilder::CreateCondBr),
            InstanceMethod("CreateSwitch", &IRBuilder::CreateSwitch),
            InstanceMethod("CreateIndirectBr", &IRBuilder::CreateIndirectBr),
            InstanceMethod("CreateInvoke", &IRBuilder::CreateInvoke),
            InstanceMethod("CreateResume", &IRBuilder::CreateResume),
            InstanceMethod("CreateUnreachable", &IRBuilder::CreateUnreachable),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Binary Operators
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateAdd", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateAdd>),
            InstanceMethod("CreateFAdd", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFAdd>),
            InstanceMethod("CreateSub", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateSub>),
            InstanceMethod("CreateFSub", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFSub>),
            InstanceMethod("CreateMul", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateMul>),
            InstanceMethod("CreateFMul", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFMul>),
            InstanceMethod("CreateSDiv", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateSDiv>),
            InstanceMethod("CreateUDiv", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateUDiv>),
            InstanceMethod("CreateFDiv", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFDiv>),
            InstanceMethod("CreateSRem", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateSRem>),
            InstanceMethod("CreateURem", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateURem>),
            InstanceMethod("CreateFRem", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFRem>),
            InstanceMethod("CreateAnd", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateAnd>),
            InstanceMethod("CreateOr", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateOr>),
            InstanceMethod("CreateXor", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateXor>),
            InstanceMethod("CreateShl", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateShl>),
            InstanceMethod("CreateAShr", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateAShr>),
            InstanceMethod("CreateLShr", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateLShr>),
            InstanceMethod("CreateNeg", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateNeg>),
            InstanceMethod("CreateFNeg", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateFNeg>),
            InstanceMethod("CreateNot", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateNot>),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Memory Instructions
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateAlloca", &IRBuilder::CreateAlloca),
            InstanceMethod("CreateLoad", &IRBuilder::CreateLoad),
            InstanceMethod("CreateStore", &IRBuilder::CreateStore),
            InstanceMethod("CreateGEP", &IRBuilder::CreateGEP),
            InstanceMethod("CreateInBoundsGEP", &IRBuilder::CreateInBoundsGEP),
            InstanceMethod("CreateGlobalStringPtr", &IRBuilder::CreateGlobalStringPtr),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Cast/Conversion Operators
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateTrunc", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateTrunc>),
            InstanceMethod("CreateZExt", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateZExt>),
            InstanceMethod("CreateSExt", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateSExt>),
            InstanceMethod("CreateZExtOrTrunc", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateZExtOrTrunc>),
            InstanceMethod("CreateSExtOrTrunc", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateSExtOrTrunc>),
            InstanceMethod("CreateFPToUI", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateFPToUI>),
            InstanceMethod("CreateFPToSI", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateFPToSI>),
            InstanceMethod("CreateUIToFP", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateUIToFP>),
            InstanceMethod("CreateSIToFP", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateSIToFP>),
            InstanceMethod("CreateFPTrunc", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateFPTrunc>),
            InstanceMethod("CreateFPExt", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateFPExt>),
            InstanceMethod("CreatePtrToInt", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreatePtrToInt>),
            InstanceMethod("CreateIntToPtr", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateIntToPtr>),
            InstanceMethod("CreateBitCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateBitCast>),
            InstanceMethod("CreateAddrSpaceCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateAddrSpaceCast>),
            InstanceMethod("CreateZExtOrBitCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateZExtOrBitCast>),
            InstanceMethod("CreateSExtOrBitCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateSExtOrBitCast>),
            InstanceMethod("CreateTruncOrBitCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateTruncOrBitCast>),
            InstanceMethod("CreatePointerCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreatePointerCast>),
            InstanceMethod("CreatePointerBitCastOrAddrSpaceCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreatePointerBitCastOrAddrSpaceCast>),
            InstanceMethod("CreateIntCast", &IRBuilder::CreateIntCast),
            InstanceMethod("CreateBitOrPointerCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateBitOrPointerCast>),
            InstanceMethod("CreateFPCast", &IRBuilder::CreateCastFactory<&LLVMIRBuilder::CreateFPCast>),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Compare Instructions
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateICmpEQ", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpEQ>),
            InstanceMethod("CreateICmpNE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpNE>),
            InstanceMethod("CreateICmpSGE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpSGE>),
            InstanceMethod("CreateICmpSGT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpSGT>),
            InstanceMethod("CreateICmpSLE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpSLE>),
            InstanceMethod("CreateICmpSLT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpSLT>),
            InstanceMethod("CreateICmpUGE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpUGE>),
            InstanceMethod("CreateICmpUGT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpUGT>),
            InstanceMethod("CreateICmpULE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpULE>),
            InstanceMethod("CreateICmpULT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateICmpULT>),
            InstanceMethod("CreateFCmpOEQ", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpOEQ>),
            InstanceMethod("CreateFCmpONE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpONE>),
            InstanceMethod("CreateFCmpOGE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpOGE>),
            InstanceMethod("CreateFCmpOGT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpOGT>),
            InstanceMethod("CreateFCmpOLE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpOLE>),
            InstanceMethod("CreateFCmpOLT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpOLT>),
            InstanceMethod("CreateFCmpUEQ", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpUEQ>),
            InstanceMethod("CreateFCmpUNE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpUNE>),
            InstanceMethod("CreateFCmpUGE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpUGE>),
            InstanceMethod("CreateFCmpUGT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpUGT>),
            InstanceMethod("CreateFCmpULE", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpULE>),
            InstanceMethod("CreateFCmpULT", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreateFCmpULT>),

            //===--------------------------------------------------------------------===//
            // Instruction creation methods: Other Instructions
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreatePHI", &IRBuilder::CreatePHI),
            InstanceMethod("CreateCall", &IRBuilder::CreateCall),
            InstanceMethod("CreateSelect", &IRBuilder::CreateSelect),
            InstanceMethod("CreateExtractValue", &IRBuilder::CreateExtractValue),
            InstanceMethod("CreateInsertValue", &IRBuilder::CreateInsertValue),
            InstanceMethod("CreateLandingPad", &IRBuilder::CreateLandingPad),

            //===--------------------------------------------------------------------===//
            // Utility creation methods
            //===--------------------------------------------------------------------===//

            InstanceMethod("CreateIsNull", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateIsNull>),
            InstanceMethod("CreateIsNotNull", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateIsNotNull>),
            InstanceMethod("CreatePtrDiff", &IRBuilder::binOpFactory<&LLVMIRBuilder::CreatePtrDiff>)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("IRBuilder", func);
}

bool IRBuilder::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

LLVMIRBuilder *IRBuilder::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IRBuilder::IRBuilder(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (info.IsConstructCall()) {
        unsigned argsLen = info.Length();
        if (argsLen == 1) {
            if (LLVMContext::IsClassOf(info[0])) {
                llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
                builder = new llvm::IRBuilder(context);
                return;
            } else if (BasicBlock::IsClassOf(info[0])) {
                llvm::BasicBlock *theBB = BasicBlock::Extract(info[0]);
                builder = new llvm::IRBuilder(theBB);
                return;
            } else if (Instruction::IsClassOf(info[0])) {
                llvm::Instruction *ip = Instruction::Extract(info[0]);
                builder = new llvm::IRBuilder(ip);
                return;
            }
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::constructor);
}

LLVMIRBuilder *IRBuilder::getLLVMPrimitive() {
    return builder;
}

//===--------------------------------------------------------------------===//
// Builder configuration methods
//===--------------------------------------------------------------------===//

void IRBuilder::ClearInsertionPoint(const Napi::CallbackInfo &info) {
    builder->ClearInsertionPoint();
}

Napi::Value IRBuilder::GetInsertBlock(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::BasicBlock *basicBlock = builder->GetInsertBlock();
    if (basicBlock) {
        return BasicBlock::New(env, basicBlock);
    }
    return env.Null();
}

void IRBuilder::SetInsertPoint(const Napi::CallbackInfo &info) {
    if (info.Length() >= 1) {
        if (BasicBlock::IsClassOf(info[0])) {
            llvm::BasicBlock *bb = BasicBlock::Extract(info[0]);
            builder->SetInsertPoint(bb);
            return;
        } else if (Instruction::IsClassOf(info[0])) {
            llvm::Instruction *inst = Instruction::Extract(info[0]);
            builder->SetInsertPoint(inst);
            return;
        }
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IRBuilder::SetInsertPoint);
}

void IRBuilder::SetCurrentDebugLocation(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1) {
        if (DebugLoc::IsClassOf(info[0])) {
            llvm::DebugLoc *location = DebugLoc::Extract(info[0]);
            builder->SetCurrentDebugLocation(*location);
            return;
        } else if (DILocation::IsClassOf(info[0])) {
            llvm::DILocation *location = DILocation::Extract(info[0]);
            builder->SetCurrentDebugLocation(location);
            return;
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::SetCurrentDebugLocation);
}

Napi::Function IRBuilder::InsertPoint::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "InsertPoint", {
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    return func;
}

Napi::Object IRBuilder::InsertPoint::New(Napi::Env env, llvm::IRBuilderBase::InsertPoint insertPoint) {
    tmpInsertPoint = insertPoint;
    return constructor.New({});
}

bool IRBuilder::InsertPoint::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::IRBuilderBase::InsertPoint IRBuilder::InsertPoint::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IRBuilder::InsertPoint::InsertPoint(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::InsertPoint::constructor);
    }
    if (tmpInsertPoint.isSet()) {
        insertPoint = tmpInsertPoint;
        tmpInsertPoint = llvm::IRBuilderBase::InsertPoint();
    }
}

llvm::IRBuilderBase::InsertPoint IRBuilder::InsertPoint::getLLVMPrimitive() {
    return insertPoint;
}

Napi::Value IRBuilder::saveIP(const Napi::CallbackInfo &info) {
    return InsertPoint::New(info.Env(), builder->saveIP());
}

Napi::Value IRBuilder::saveAndClearIP(const Napi::CallbackInfo &info) {
    return InsertPoint::New(info.Env(), builder->saveAndClearIP());
}

void IRBuilder::restoreIP(const Napi::CallbackInfo &info) {
    if (info.Length() == 1 && InsertPoint::IsClassOf(info[0])) {
        builder->restoreIP(InsertPoint::Extract(info[0]));
    }
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IRBuilder::restoreIP);
}

//===--------------------------------------------------------------------===//
// Miscellaneous creation methods.
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::CreateGlobalString(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && info[0].IsString() ||
        argsLen == 2 && info[0].IsString() && info[1].IsString() ||
        argsLen == 3 && info[0].IsString() && info[1].IsString() && info[2].IsNumber() ||
        argsLen == 4 && info[0].IsString() && info[1].IsString() && info[2].IsNumber() && Module::IsClassOf(info[3])) {
        const std::string &str = std::string(info[0].As<Napi::String>());
        const std::string &name = argsLen >= 2 ? std::string(info[1].As<Napi::String>()) : "";
        unsigned addrSpace = argsLen >= 3 ? info[2].As<Napi::Number>() : 0;
        llvm::Module *module = argsLen == 4 ? Module::Extract(info[3]) : nullptr;
        llvm::GlobalVariable *globalStr = builder->CreateGlobalString(str, name, addrSpace, module);
        return GlobalVariable::New(env, globalStr);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateGlobalString);
}

Napi::Value IRBuilder::getInt1(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsBoolean()) {
        bool value = info[0].As<Napi::Boolean>();
        return ConstantInt::New(env, builder->getInt1(value));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt1);
}

Napi::Value IRBuilder::getIntN(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
        unsigned numBits = info[0].As<Napi::Number>();
        uint64_t value = info[1].As<Napi::Number>().Int64Value();
        return ConstantInt::New(env, builder->getIntN(numBits, value));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntN);
}

Napi::Value IRBuilder::getInt(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && APInt::IsClassOf(info[0])) {
        llvm::APInt &value = APInt::Extract(info[0]);
        return ConstantInt::New(env, builder->getInt(value));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt);
}

//===--------------------------------------------------------------------===//
// Type creation methods
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::getIntNTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsNumber()) {
        unsigned numBits = info[0].As<Napi::Number>();
        return IntegerType::New(env, builder->getIntNTy(numBits));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntNTy);
}

Napi::Value IRBuilder::getInt8PtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 0 || argsLen == 1 && info[0].IsNumber()) {
        unsigned addrSpace = argsLen == 1 ? info[0].As<Napi::Number>() : 0;
        llvm::PointerType *type = builder->getInt8PtrTy(addrSpace);
        return PointerType::New(env, type);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt8PtrTy);
}

Napi::Value IRBuilder::getIntPtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && DataLayout::IsClassOf(info[0]) ||
        argsLen == 2 && DataLayout::IsClassOf(info[0]) && info[1].IsNumber()) {
        llvm::DataLayout &dl = DataLayout::Extract(info[0]);
        unsigned addrSpace = argsLen >= 2 ? info[1].As<Napi::Number>() : 0;
        llvm::IntegerType *type = builder->getIntPtrTy(dl, addrSpace);
        return IntegerType::New(env, type);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntPtrTy);
}

//===--------------------------------------------------------------------===//
// Instruction creation methods: Terminators
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::CreateRetVoid(const Napi::CallbackInfo &info) {
    return ReturnInst::New(info.Env(), builder->CreateRetVoid());
}

Napi::Value IRBuilder::CreateRet(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen >= 1 && Value::IsClassOf(info[0])) {
        llvm::ReturnInst *ret = builder->CreateRet(Value::Extract(info[0]));
        return ReturnInst::New(env, ret);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateRet);
}

Napi::Value IRBuilder::CreateBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && BasicBlock::IsClassOf(info[0])) {
        llvm::BasicBlock *destBB = BasicBlock::Extract(info[0]);
        llvm::BranchInst *branch = builder->CreateBr(destBB);
        return BranchInst::New(env, branch);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateBr);
}

Napi::Value IRBuilder::CreateCondBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 3 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2])) {
        llvm::Value *cond = Value::Extract(info[0]);
        llvm::BasicBlock *thenBB = BasicBlock::Extract(info[1]);
        llvm::BasicBlock *elseBB = BasicBlock::Extract(info[2]);
        llvm::BranchInst *branch = builder->CreateCondBr(cond, thenBB, elseBB);
        return BranchInst::New(env, branch);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateCondBr);
}

Napi::Value IRBuilder::CreateSwitch(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) ||
        argsLen == 3 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && info[2].IsNumber()) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::BasicBlock *dest = BasicBlock::Extract(info[1]);
        unsigned numCases = argsLen >= 3 ? info[2].As<Napi::Number>() : 10;
        llvm::SwitchInst *switchInst = builder->CreateSwitch(value, dest, numCases);
        return SwitchInst::New(env, switchInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateSwitch);
}

Napi::Value IRBuilder::CreateIndirectBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && Value::IsClassOf(info[0]) ||
        argsLen == 2 && Value::IsClassOf(info[0]) && info[1].IsNumber()) {
        llvm::Value *addr = Value::Extract(info[0]);
        unsigned numDests = argsLen == 2 ? info[1].As<Napi::Number>() : 10;
        llvm::IndirectBrInst *indirectBrInst = builder->CreateIndirectBr(addr, numDests);
        return IndirectBrInst::New(env, indirectBrInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateIndirectBr);
}

Napi::Value IRBuilder::CreateInvoke(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    llvm::InvokeInst *invokeInst = nullptr;
    std::vector<llvm::Value *> calleeArgs;
    if (argsLen == 3 && Function::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) ||
        argsLen == 4 && Function::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsString()) {
        llvm::Function *callee = Function::Extract(info[0]);
        llvm::BasicBlock *normalDest = BasicBlock::Extract(info[1]);
        llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[2]);
        std::string name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
        invokeInst = builder->CreateInvoke(callee, normalDest, unwindDest, llvm::None, name);
    } else if (argsLen == 4 && Function::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsArray() ||
               argsLen == 5 && Function::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsArray() && info[4].IsString()) {
        if (assembleArray<WrappedValue>(info[3].As<Napi::Array>(), calleeArgs)) {
            llvm::Function *callee = Function::Extract(info[0]);
            llvm::BasicBlock *normalDest = BasicBlock::Extract(info[1]);
            llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[2]);
            std::string name = argsLen == 5 ? std::string(info[4].As<Napi::String>()) : "";
            invokeInst = builder->CreateInvoke(callee, normalDest, unwindDest, calleeArgs, name);
        }
    } else if (argsLen == 3 && FunctionCallee::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) ||
               argsLen == 4 && FunctionCallee::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsString()) {
        llvm::FunctionCallee callee = FunctionCallee::Extract(info[0]);
        llvm::BasicBlock *normalDest = BasicBlock::Extract(info[1]);
        llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[2]);
        std::string name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
        invokeInst = builder->CreateInvoke(callee, normalDest, unwindDest, llvm::None, name);
    } else if (argsLen == 4 && FunctionCallee::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsArray() ||
               argsLen == 5 && FunctionCallee::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) && info[3].IsArray() && info[4].IsString()) {
        if (assembleArray<WrappedValue>(info[3].As<Napi::Array>(), calleeArgs)) {
            llvm::FunctionCallee callee = FunctionCallee::Extract(info[0]);
            llvm::BasicBlock *normalDest = BasicBlock::Extract(info[1]);
            llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[2]);
            std::string name = argsLen == 5 ? std::string(info[4].As<Napi::String>()) : "";
            invokeInst = builder->CreateInvoke(callee, normalDest, unwindDest, calleeArgs, name);
        }
    } else if (argsLen == 4 && FunctionType::IsClassOf(info[0]) && Function::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) &&
               BasicBlock::IsClassOf(info[3]) ||
               argsLen == 5 && FunctionType::IsClassOf(info[0]) && Function::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) &&
               BasicBlock::IsClassOf(info[3]) && info[4].IsString()) {
        llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
        llvm::Function *callee = Function::Extract(info[1]);
        llvm::BasicBlock *normalDest = BasicBlock::Extract(info[2]);
        llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[3]);
        std::string name = argsLen == 5 ? std::string(info[4].As<Napi::String>()) : "";
        invokeInst = builder->CreateInvoke(funcType, callee, normalDest, unwindDest, llvm::None, name);
    } else if (argsLen == 5 && FunctionType::IsClassOf(info[0]) && Function::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) &&
               BasicBlock::IsClassOf(info[3]) && info[4].IsArray() ||
               argsLen == 6 && FunctionType::IsClassOf(info[0]) && Function::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2]) &&
               BasicBlock::IsClassOf(info[3]) && info[4].IsArray() && info[5].IsString()) {
        if (assembleArray<WrappedValue>(info[4].As<Napi::Array>(), calleeArgs)) {
            llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
            llvm::Function *callee = Function::Extract(info[1]);
            llvm::BasicBlock *normalDest = BasicBlock::Extract(info[2]);
            llvm::BasicBlock *unwindDest = BasicBlock::Extract(info[3]);
            std::string name = argsLen == 6 ? std::string(info[5].As<Napi::String>()) : "";
            invokeInst = builder->CreateInvoke(funcType, callee, normalDest, unwindDest, calleeArgs, name);
        }
    }
    if (invokeInst) {
        return InvokeInst::New(env, invokeInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateInvoke);
}

Napi::Value IRBuilder::CreateResume(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && Value::IsClassOf(info[0])) {
        llvm::ResumeInst *resumeInst = builder->CreateResume(Value::Extract(info[0]));
        return ResumeInst::New(info.Env(), resumeInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateResume);
}

Napi::Value IRBuilder::CreateUnreachable(const Napi::CallbackInfo &info) {
    return UnreachableInst::New(info.Env(), builder->CreateUnreachable());
}

//===--------------------------------------------------------------------===//
// Instruction creation methods: Memory Instructions
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::CreateAlloca(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && Type::IsClassOf(info[0]) ||
        argsLen == 2 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
        argsLen >= 3 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *arraySize = argsLen >= 2 ? Value::Extract(info[1]) : nullptr;
        std::string name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        llvm::AllocaInst *alloca = builder->CreateAlloca(type, arraySize, name);
        return AllocaInst::New(env, alloca);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateAlloca);
}

Napi::Value IRBuilder::CreateLoad(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
        argsLen >= 3 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        std::string name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        llvm::LoadInst *load = builder->CreateLoad(type, ptr, name);
        return LoadInst::New(env, load);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateLoad);
}

Napi::Value IRBuilder::CreateStore(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        llvm::StoreInst *store = builder->CreateStore(value, ptr);
        return StoreInst::New(env, store);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateStore);
}

Napi::Value IRBuilder::CreateGEP(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    std::vector<llvm::Value *> idxList;
    if (argsLen == 3 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
        argsLen == 4 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[3].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        const std::string &name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
        if (Value::IsClassOf(info[2])) {
            llvm::Value *idx = Value::Extract(info[2]);
            return Value::New(env, builder->CreateGEP(type, ptr, idx, name));
        } else if (info[2].IsArray() && assembleArray<WrappedValue>(info[2].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateGEP(type, ptr, idxList, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateGEP);
}

Napi::Value IRBuilder::CreateInBoundsGEP(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    std::vector<llvm::Value *> idxList;
    if (argsLen == 3 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
        argsLen == 4 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[3].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        const std::string &name = argsLen >= 4 ? std::string(info[3].As<Napi::String>()) : "";
        if (Value::IsClassOf(info[2])) {
            llvm::Value *idx = Value::Extract(info[2]);
            return Value::New(env, builder->CreateInBoundsGEP(type, ptr, idx, name));
        } else if (info[2].IsArray() && assembleArray<WrappedValue>(info[2].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateInBoundsGEP(type, ptr, idxList, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateInBoundsGEP);
}

Napi::Value IRBuilder::CreateGlobalStringPtr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 1 && info[0].IsString() ||
        argsLen == 2 && info[0].IsString() && info[1].IsString() ||
        argsLen == 3 && info[0].IsString() && info[1].IsString() && info[2].IsNumber() ||
        argsLen == 4 && info[0].IsString() && info[1].IsString() && info[2].IsNumber() && Module::IsClassOf(info[3])) {
        const std::string &str = std::string(info[0].As<Napi::String>());
        const std::string &name = argsLen >= 2 ? std::string(info[1].As<Napi::String>()) : "";
        unsigned addrSpace = argsLen >= 3 ? info[2].As<Napi::Number>() : 0;
        llvm::Module *module = argsLen == 4 ? Module::Extract(info[3]) : nullptr;
        llvm::Constant *globalStrPtr = builder->CreateGlobalStringPtr(str, name, addrSpace, module);
        return Constant::New(env, globalStrPtr);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateGlobalStringPtr);
}

//===--------------------------------------------------------------------===//
// Instruction creation methods: Cast/Conversion Operators
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::CreateIntCast(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 3 && Value::IsClassOf(info[0]) && Type::IsClassOf(info[1]) && info[2].IsBoolean() ||
        argsLen == 4 && Value::IsClassOf(info[0]) && Type::IsClassOf(info[1]) && info[2].IsBoolean() && info[3].IsString()) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Type *destType = Type::Extract(info[1]);
        bool isSigned = info[2].As<Napi::Boolean>();
        const std::string &name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
        return Value::New(env, builder->CreateIntCast(value, destType, isSigned, name));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateIntCast);
}

//===--------------------------------------------------------------------===//
// Instruction creation methods: Other Instructions
//===--------------------------------------------------------------------===//

Napi::Value IRBuilder::CreatePHI(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Type::IsClassOf(info[0]) && info[1].IsNumber() ||
        argsLen == 3 && Type::IsClassOf(info[0]) && info[1].IsNumber() && info[2].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        unsigned numReservedValues = info[1].As<Napi::Number>();
        const std::string &name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
        llvm::PHINode *phiNode = builder->CreatePHI(type, numReservedValues, name);
        return PHINode::New(env, phiNode);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreatePHI);
}

Napi::Value IRBuilder::CreateCall(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    llvm::CallInst *callInst = nullptr;
    std::vector<llvm::Value *> calleeArgs;
    if (argsLen == 1 && Function::IsClassOf(info[0]) ||
        argsLen == 2 && Function::IsClassOf(info[0]) && info[1].IsString()) {
        llvm::Function *callee = Function::Extract(info[0]);
        std::string name = argsLen == 2 ? std::string(info[1].As<Napi::String>()) : "";
        callInst = builder->CreateCall(callee, llvm::None, name);
    } else if (argsLen == 2 && Function::IsClassOf(info[0]) && info[1].IsArray() ||
               argsLen == 3 && Function::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsString()) {
        if (assembleArray<WrappedValue>(info[1].As<Napi::Array>(), calleeArgs)) {
            llvm::Function *callee = Function::Extract(info[0]);
            std::string name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
            callInst = builder->CreateCall(callee, calleeArgs, name);
        }
    } else if (argsLen == 1 && FunctionCallee::IsClassOf(info[0]) ||
               argsLen == 2 && FunctionCallee::IsClassOf(info[0]) && info[1].IsString()) {
        llvm::FunctionCallee callee = FunctionCallee::Extract(info[0]);
        std::string name = argsLen == 2 ? std::string(info[1].As<Napi::String>()) : "";
        callInst = builder->CreateCall(callee, llvm::None, name);
    } else if (argsLen == 2 && FunctionCallee::IsClassOf(info[0]) && info[1].IsArray() ||
               argsLen == 3 && FunctionCallee::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsString()) {
        if (assembleArray<WrappedValue>(info[1].As<Napi::Array>(), calleeArgs)) {
            llvm::FunctionCallee callee = FunctionCallee::Extract(info[0]);
            std::string name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
            callInst = builder->CreateCall(callee, calleeArgs, name);
        }
    } else if (argsLen == 2 && FunctionType::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
               argsLen == 3 && FunctionType::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsString()) {
        llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
        llvm::Value *callee = Value::Extract(info[1]);
        std::string name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
        callInst = builder->CreateCall(funcType, callee, llvm::None, name);
    } else if (argsLen == 3 && FunctionType::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsArray() ||
               argsLen == 4 && FunctionType::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsArray() && info[3].IsString()) {
        if (assembleArray<WrappedValue>(info[2].As<Napi::Array>(), calleeArgs)) {
            llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
            llvm::Value *callee = Value::Extract(info[1]);
            std::string name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
            callInst = builder->CreateCall(funcType, callee, calleeArgs, name);
        }
    }
    if (callInst) {
        return CallInst::New(env, callInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateCall);
}

Napi::Value IRBuilder::CreateSelect(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 3 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && Value::IsClassOf(info[2]) ||
        argsLen == 4 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && Value::IsClassOf(info[2]) && info[3].IsString()) {
        llvm::Value *cond = Value::Extract(info[0]);
        llvm::Value *trueValue = Value::Extract(info[1]);
        llvm::Value *falseValue = Value::Extract(info[2]);
        const std::string &name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
        return Value::New(env, builder->CreateSelect(cond, trueValue, falseValue, name));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateSelect);
}

Napi::Value IRBuilder::CreateExtractValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Value::IsClassOf(info[0]) && info[1].IsArray() ||
        argsLen == 3 && Value::IsClassOf(info[0]) && info[1].IsArray() && info[2].IsString()) {
        llvm::Value *agg = Value::Extract(info[0]);
        const auto &idxArr = info[1].As<Napi::Array>();
        unsigned numIdxs = idxArr.Length();
        std::vector<unsigned> idxs(numIdxs);
        bool convertSuccess = true;
        for (unsigned i = 0; i < numIdxs; ++i) {
            const auto &idx = Napi::Value(idxArr[i]);
            if (idx.IsNumber()) {
                idxs[i] = idx.As<Napi::Number>();
            } else {
                convertSuccess = false;
                break;
            }
        }
        if (convertSuccess) {
            const std::string &name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
            return Value::New(env, builder->CreateExtractValue(agg, idxs, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateExtractValue);
}

Napi::Value IRBuilder::CreateInsertValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 3 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsArray() ||
        argsLen == 4 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsArray() && info[3].IsString()) {
        llvm::Value *agg = Value::Extract(info[0]);
        llvm::Value *value = Value::Extract(info[1]);
        const auto &idxArr = info[2].As<Napi::Array>();
        unsigned numIdxs = idxArr.Length();
        std::vector<unsigned> idxs(numIdxs);
        bool convertSuccess = true;
        for (unsigned i = 0; i < numIdxs; ++i) {
            const auto &idx = Napi::Value(idxArr[i]);
            if (idx.IsNumber()) {
                idxs[i] = idx.As<Napi::Number>();
            } else {
                convertSuccess = false;
                break;
            }
        }
        if (convertSuccess) {
            const std::string &name = argsLen == 4 ? std::string(info[3].As<Napi::String>()) : "";
            return Value::New(env, builder->CreateInsertValue(agg, value, idxs, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateInsertValue);
}

Napi::Value IRBuilder::CreateLandingPad(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Type::IsClassOf(info[0]) && info[1].IsNumber() ||
        argsLen == 3 && Type::IsClassOf(info[0]) && info[1].IsNumber() && info[2].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        unsigned numClauses = info[1].As<Napi::Number>();
        const std::string &name = argsLen == 3 ? std::string(info[2].As<Napi::String>()) : "";
        llvm::LandingPadInst *lpInst = builder->CreateLandingPad(type, numClauses, name);
        return LandingPadInst::New(env, lpInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateLandingPad);
}
