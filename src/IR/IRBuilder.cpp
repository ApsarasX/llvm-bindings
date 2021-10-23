#include "IR/IR.h"
#include "ADT/APInt.h"
#include "Util/Util.h"

void IRBuilder::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IRBuilder", {
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
            InstanceMethod("CreateNeg", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateNeg>),
            InstanceMethod("CreateFNeg", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateFNeg>),
            InstanceMethod("CreateNot", &IRBuilder::unOpFactory<&LLVMIRBuilder::CreateNot>),
            InstanceMethod("CreateAlloca", &IRBuilder::createAlloca),
            InstanceMethod("CreateBr", &IRBuilder::createBr),
            InstanceMethod("CreateCall", &IRBuilder::createCall),
            InstanceMethod("CreateCondBr", &IRBuilder::createCondBr),
            InstanceMethod("CreateUnreachable", &IRBuilder::createUnreachable),
            InstanceMethod("CreateLoad", &IRBuilder::createLoad),
            InstanceMethod("CreateRet", &IRBuilder::createRet),
            InstanceMethod("CreateRetVoid", &IRBuilder::createRetVoid),
            InstanceMethod("CreateSwitch", &IRBuilder::createSwitch),
            InstanceMethod("CreateStore", &IRBuilder::createStore),
            InstanceMethod("CreateGEP", &IRBuilder::createGEP),
            InstanceMethod("CreateInBoundsGEP", &IRBuilder::createInBoundsGEP),
            InstanceMethod("CreateGlobalString", &IRBuilder::createGlobalString),
            InstanceMethod("CreateGlobalStringPtr", &IRBuilder::createGlobalStringPtr),
            InstanceMethod("CreatePHI", &IRBuilder::createPHI),
            InstanceMethod("CreateSelect", &IRBuilder::createSelect),

            InstanceMethod("CreateTrunc", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateTrunc>),
            InstanceMethod("CreateZExt", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateZExt>),
            InstanceMethod("CreateSExt", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateSExt>),
            InstanceMethod("CreateZExtOrTrunc", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateZExtOrTrunc>),
            InstanceMethod("CreateSExtOrTrunc", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateSExtOrTrunc>),
            InstanceMethod("CreateFPToUI", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateFPToUI>),
            InstanceMethod("CreateFPToSI", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateFPToSI>),
            InstanceMethod("CreateUIToFP", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateUIToFP>),
            InstanceMethod("CreateSIToFP", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateSIToFP>),
            InstanceMethod("CreateFPTrunc", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateFPTrunc>),
            InstanceMethod("CreateFPExt", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateFPExt>),
            InstanceMethod("CreatePtrToInt", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreatePtrToInt>),
            InstanceMethod("CreateIntToPtr", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateIntToPtr>),
            InstanceMethod("CreateBitCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateBitCast>),
            InstanceMethod("CreateAddrSpaceCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateAddrSpaceCast>),
            InstanceMethod("CreateZExtOrBitCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateZExtOrBitCast>),
            InstanceMethod("CreateSExtOrBitCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateSExtOrBitCast>),
            InstanceMethod("CreateTruncOrBitCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateTruncOrBitCast>),
            InstanceMethod("CreatePointerCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreatePointerCast>),
            InstanceMethod("CreatePointerBitCastOrAddrSpaceCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreatePointerBitCastOrAddrSpaceCast>),
            InstanceMethod("CreateIntCast", &IRBuilder::createIntCast),
            InstanceMethod("CreateBitOrPointerCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateBitOrPointerCast>),
            InstanceMethod("CreateFPCast", &IRBuilder::createCastFactory<&LLVMIRBuilder::CreateFPCast>),
            InstanceMethod("getInt1", &IRBuilder::getInt1),
            InstanceMethod("getTrue", &IRBuilder::getBoolFactory<&LLVMIRBuilder::getTrue>),
            InstanceMethod("getFalse", &IRBuilder::getBoolFactory<&LLVMIRBuilder::getFalse>),
            InstanceMethod("getInt8", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt8>),
            InstanceMethod("getInt16", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt16>),
            InstanceMethod("getInt32", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt32>),
            InstanceMethod("getInt64", &IRBuilder::getIntFactory<&LLVMIRBuilder::getInt64>),
            InstanceMethod("getIntN", &IRBuilder::getIntN),
            InstanceMethod("getInt", &IRBuilder::getInt),
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

            InstanceMethod("SetInsertPoint", &IRBuilder::setInsertPoint),
            InstanceMethod("GetInsertBlock", &IRBuilder::getInsertBlock),
            InstanceMethod("ClearInsertionPoint", &IRBuilder::clearInsertionPoint),
            InstanceMethod("saveIP", &IRBuilder::saveIP),
            InstanceMethod("saveAndClearIP", &IRBuilder::saveAndClearIP),
            InstanceMethod("restoreIP", &IRBuilder::restoreIP),

            StaticValue("InsertPoint", InsertPoint::Init(env, exports))
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("IRBuilder", func);
}

bool IRBuilder::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

LLVMIRBuilder *IRBuilder::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

IRBuilder::IRBuilder(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall() || info.Length() == 0 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::constructor);
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    builder = new llvm::IRBuilder(context);
}

LLVMIRBuilder *IRBuilder::getLLVMPrimitive() {
    return builder;
}

Napi::Value IRBuilder::createAlloca(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
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

Napi::Value IRBuilder::createBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && BasicBlock::IsClassOf(info[0])) {
        llvm::BasicBlock *destBB = BasicBlock::Extract(info[0]);
        llvm::BranchInst *branch = builder->CreateBr(destBB);
        return BranchInst::New(env, branch);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateBr);
}

bool assembleValueArray(Napi::Array values, std::vector<llvm::Value *> &valueArray) {
    int size = values.Length();
    valueArray.resize(size);
    for (int i = 0; i < size; ++i) {
        if (!Value::IsClassOf(values[i])) {
            return false;
        }
        valueArray[i] = Value::Extract(values[i]);
    }
    return true;
}

Napi::Value IRBuilder::createCall(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    llvm::CallInst *call = nullptr;
    std::vector<llvm::Value *> calleeArgs;
    if (argsLen == 1 && Function::IsClassOf(info[0])) {
        llvm::Function *callee = Function::Extract(info[0]);
        call = builder->CreateCall(callee);
    } else if (argsLen >= 2 && Function::IsClassOf(info[0]) && info[1].IsArray() && (argsLen == 2 || argsLen >= 3 && info[2].IsString())) {
        llvm::Function *callee = Function::Extract(info[0]);
        if (assembleValueArray(info[1].As<Napi::Array>(), calleeArgs)) {
            std::string name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
            call = builder->CreateCall(callee, calleeArgs, name);
        }
    } else if (argsLen >= 3 && FunctionType::IsClassOf(info[0]) &&
               Value::IsClassOf(info[1]) && info[2].IsArray() &&
               (argsLen == 3 || argsLen >= 4 && info[3].IsString())) {
        llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
        llvm::Value *callee = Value::Extract(info[1]);
        if (assembleValueArray(info[1].As<Napi::Array>(), calleeArgs)) {
            std::string name = argsLen >= 3 ? std::string(info[3].As<Napi::String>()) : "";
            call = builder->CreateCall(funcType, callee, calleeArgs, name);
        }
    }
    if (call) {
        return CallInst::New(env, call);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateCall);
}

Napi::Value IRBuilder::createCondBr(const Napi::CallbackInfo &info) {
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

Napi::Value IRBuilder::createUnreachable(const Napi::CallbackInfo &info) {
    return UnreachableInst::New(info.Env(), builder->CreateUnreachable());
}

Napi::Value IRBuilder::createLoad(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
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

Napi::Value IRBuilder::createRet(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen >= 1 && Value::IsClassOf(info[0])) {
        llvm::ReturnInst *ret = builder->CreateRet(Value::Extract(info[0]));
        return ReturnInst::New(env, ret);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateRet);
}

Napi::Value IRBuilder::createRetVoid(const Napi::CallbackInfo &info) {
    return ReturnInst::New(info.Env(), builder->CreateRetVoid());
}

Napi::Value IRBuilder::createSwitch(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen == 2 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) ||
        argsLen >= 3 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && info[2].IsNumber()) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::BasicBlock *dest = BasicBlock::Extract(info[1]);
        unsigned numCases = argsLen >= 3 ? info[2].As<Napi::Number>() : 10;
        llvm::SwitchInst *switchInst = builder->CreateSwitch(value, dest, numCases);
        return SwitchInst::New(env, switchInst);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateSwitch);
}

Napi::Value IRBuilder::createStore(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        llvm::StoreInst *store = builder->CreateStore(value, ptr);
        return StoreInst::New(env, store);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateStore);
}

Napi::Value IRBuilder::createGEP(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    std::vector<llvm::Value *> idxList;
    if (argsLen >= 2 && Value::IsClassOf(info[0]) && (argsLen == 2 || argsLen >= 3 && info[2].IsString())) {
        llvm::Value *ptr = Value::Extract(info[0]);
        const std::string &name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        if (Value::IsClassOf(info[1])) {
            llvm::Value *idx = Value::Extract(info[1]);
            return Value::New(env, builder->CreateGEP(ptr, idx, name));
        } else if (info[1].IsArray() && assembleValueArray(info[1].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateGEP(ptr, idxList, name));
        }
    } else if (argsLen >= 3 &&
               Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) &&
               (argsLen == 3 || argsLen >= 4 && info[3].IsString())) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        const std::string &name = argsLen >= 4 ? std::string(info[3].As<Napi::String>()) : "";
        if (Value::IsClassOf(info[2])) {
            llvm::Value *idx = Value::Extract(info[2]);
            return Value::New(env, builder->CreateGEP(type, ptr, idx, name));
        } else if (info[2].IsArray() && assembleValueArray(info[2].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateGEP(type, ptr, idxList, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateGEP);
}

Napi::Value IRBuilder::createInBoundsGEP(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    std::vector<llvm::Value *> idxList;
    if (argsLen >= 2 &&
        Value::IsClassOf(info[0]) && info[1].IsArray() &&
        (argsLen == 2 || argsLen >= 3 && info[2].IsString())) {
        llvm::Value *ptr = Value::Extract(info[0]);
        const std::string &name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
        if (assembleValueArray(info[1].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateInBoundsGEP(ptr, idxList, name));
        }
    } else if (argsLen >= 3 &&
               Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) &&
               (argsLen == 3 || argsLen >= 4 && info[3].IsString())) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        const std::string &name = argsLen >= 4 ? std::string(info[3].As<Napi::String>()) : "";
        if (Value::IsClassOf(info[2])) {
            llvm::Value *idx = Value::Extract(info[2]);
            return Value::New(env, builder->CreateInBoundsGEP(type, ptr, idx, name));
        } else if (info[2].IsArray() && assembleValueArray(info[2].As<Napi::Array>(), idxList)) {
            return Value::New(env, builder->CreateInBoundsGEP(type, ptr, idxList, name));
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateInBoundsGEP);
}

Napi::Value IRBuilder::getInt1(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsBoolean()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt1);
    }
    bool value = info[0].As<Napi::Boolean>();
    return ConstantInt::New(env, builder->getInt1(value));
}

Napi::Value IRBuilder::getIntN(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntN);
    }
    unsigned n = info[0].As<Napi::Number>();
    uint64_t value = info[1].As<Napi::Number>().Int64Value();
    return ConstantInt::New(env, builder->getIntN(n, value));
}

Napi::Value IRBuilder::getInt(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !APInt::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt);
    }
    llvm::APInt &value = APInt::Extract(info[0]);
    return ConstantInt::New(env, builder->getInt(value));
}

Napi::Value IRBuilder::getIntNTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntNTy);
    }
    unsigned n = info[0].As<Napi::Number>();
    return IntegerType::New(env, builder->getIntNTy(n));
}

Napi::Value IRBuilder::getInt8PtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen >= 1 && !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getInt8PtrTy);
    }
    unsigned addrSpace = argsLen >= 1 ? info[0].As<Napi::Number>() : 0;
    llvm::PointerType *type = builder->getInt8PtrTy(addrSpace);
    return PointerType::New(env, type);
}

Napi::Value IRBuilder::getIntPtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen == 0 || !DataLayout::IsClassOf(info[0]) || argsLen >= 2 && !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::getIntPtrTy);
    }
    llvm::DataLayout &dl = DataLayout::Extract(info[0]);
    unsigned addrSpace = argsLen >= 2 ? info[1].As<Napi::Number>() : 0;
    llvm::IntegerType *type = builder->getIntPtrTy(dl, addrSpace);
    return IntegerType::New(env, type);
}

#define createGlobalStringOrPtr(methodName, returnType) \
    Napi::Env env = info.Env(); \
    int argsLen = info.Length(); \
    if (argsLen == 0 || !info[0].IsString() || \
        argsLen >= 2 && !info[1].IsString() || \
        argsLen >= 3 && !info[2].IsNumber() || \
        argsLen >= 4 && !Module::IsClassOf(info[3])) { \
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::methodName); \
    } \
    const std::string &str = info[0].As<Napi::String>(); \
    std::string name; \
    unsigned addrSpace = 0; \
    llvm::Module *module = nullptr; \
    if (argsLen >= 2) { \
        name = info[1].As<Napi::String>(); \
    } \
    if (argsLen >= 3) { \
        addrSpace = info[2].As<Napi::Number>(); \
    } \
    if (argsLen >= 4) { \
        module = Module::Extract(info[3]); \
    } \
    llvm::returnType *result = builder->methodName(str, name, addrSpace, module); \
    return returnType::New(env, result);

Napi::Value IRBuilder::createGlobalString(const Napi::CallbackInfo &info) {
    createGlobalStringOrPtr(CreateGlobalString, GlobalVariable)
}

Napi::Value IRBuilder::createGlobalStringPtr(const Napi::CallbackInfo &info) {
    createGlobalStringOrPtr(CreateGlobalStringPtr, Constant)
}

Napi::Value IRBuilder::createPHI(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen < 2 || !Type::IsClassOf(info[0]) || !info[1].IsNumber() || argsLen >= 3 && !info[2].IsString()) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreatePHI);
    }
    llvm::Type *type = Type::Extract(info[0]);
    unsigned numReservedValues = info[1].As<Napi::Number>();
    const std::string &name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
    llvm::PHINode *phiNode = builder->CreatePHI(type, numReservedValues, name);
    return PHINode::New(env, phiNode);
}

Napi::Value IRBuilder::createSelect(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen < 3 ||
        !Value::IsClassOf(info[0]) ||
        !Value::IsClassOf(info[1]) ||
        !Value::IsClassOf(info[2]) ||
        (argsLen >= 4 && !info[3].IsString())) {
        throw Napi::TypeError::New(env, ErrMsg::Class::IRBuilder::CreateSelect);
    }
    llvm::Value *cond = Value::Extract(info[0]);
    llvm::Value *trueValue = Value::Extract(info[1]);
    llvm::Value *falseValue = Value::Extract(info[2]);
    const std::string &name = argsLen >= 4 ? std::string(info[3].As<Napi::String>()) : "";
    return Value::New(env, builder->CreateSelect(cond, trueValue, falseValue, name));
}

void IRBuilder::setInsertPoint(const Napi::CallbackInfo &info) {
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
    throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IRBuilder::setInsertPoint);
}

Napi::Value IRBuilder::getInsertBlock(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::BasicBlock *basicBlock = builder->GetInsertBlock();
    if (basicBlock) {
        return BasicBlock::New(env, basicBlock);
    }
    return env.Null();
}

void IRBuilder::clearInsertionPoint(const Napi::CallbackInfo &info) {
    builder->ClearInsertionPoint();
}

Napi::Value IRBuilder::saveIP(const Napi::CallbackInfo &info) {
    return InsertPoint::New(info.Env(), builder->saveIP());
}

Napi::Value IRBuilder::saveAndClearIP(const Napi::CallbackInfo &info) {
    return InsertPoint::New(info.Env(), builder->saveAndClearIP());
}

void IRBuilder::restoreIP(const Napi::CallbackInfo &info) {
    if (info.Length() == 0 || !InsertPoint::IsClassOf(info[0])) {
        throw Napi::TypeError::New(info.Env(), ErrMsg::Class::IRBuilder::restoreIP);
    }
    builder->restoreIP(InsertPoint::Extract(info[0]));
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
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
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
