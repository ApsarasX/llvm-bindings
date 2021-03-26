#include "IR/IRBuilder.h"
#include "IR/LLVMContext.h"
#include "IR/Type.h"
#include "IR/IntegerType.h"
#include "IR/PointerType.h"
#include "IR/FunctionType.h"
#include "IR/Value.h"
#include "IR/ConstantInt.h"
#include "IR/BasicBlock.h"
#include "IR/DataLayout.h"
#include "IR/Function.h"
#include "ADT/APInt.h"

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
            InstanceMethod("CreateAlloca", &IRBuilder::createAlloca),
            InstanceMethod("CreateBr", &IRBuilder::createBr),
            InstanceMethod("CreateCall", &IRBuilder::createCall),
            InstanceMethod("CreateCondBr", &IRBuilder::createCondBr),
            InstanceMethod("CreateLoad", &IRBuilder::createLoad),
            InstanceMethod("CreateRet", &IRBuilder::createRet),
            InstanceMethod("CreateRetVoid", &IRBuilder::createRetVoid),
            InstanceMethod("CreateStore", &IRBuilder::createStore),

            InstanceMethod("SetInsertionPoint", &IRBuilder::setInsertionPoint),

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
            InstanceMethod("getIntPtrTy", &IRBuilder::getIntPtrTy)
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
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Module constructor needs to be called with new");
    }
    if (info.Length() < 1 || !LLVMContext::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "The IRBuilder constructor needs to be called with: new (context: LLVMContext)");
    }
    llvm::LLVMContext &context = LLVMContext::Extract(info[0]);
    builder = new llvm::IRBuilder(context);
}

void IRBuilder::setInsertionPoint(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !BasicBlock::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "IRBuilder.SetInsertionPoint needs to be called with: (basicBlock: BasicBlock)");
    }
    llvm::BasicBlock *bb = BasicBlock::Extract(info[0]);
    builder->SetInsertPoint(bb);
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
        // TODO: opt here
        return Value::New(env, alloca);
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateAlloca needs to be called with: (type: Type, arraySize?: Value, name?: string)");
}

Napi::Value IRBuilder::createBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() >= 1 && BasicBlock::IsClassOf(info[0])) {
        llvm::BasicBlock *destBB = BasicBlock::Extract(info[0]);
        llvm::BranchInst *branch = builder->CreateBr(destBB);
        // TODO: opt here
        return Value::New(env, branch);
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateBr needs to be called with: (destBB: BasicBlock)");
}

bool extractCalleeArgs(Napi::Array args, std::vector<llvm::Value *> &calleeArgs) {
    int argsLen = args.Length();
    calleeArgs.resize(argsLen);
    for (int i = 0; i < argsLen; ++i) {
        if (!Value::IsClassOf(args[i])) {
            return false;
        }
        calleeArgs[i] = Value::Extract(args[i]);
    }
    return true;
}

Napi::Value IRBuilder::createCall(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    llvm::CallInst *call = nullptr;
    std::vector<llvm::Value *> calleeArgs;
    if (argsLen >= 2 && Function::IsClassOf(info[0]) && info[1].IsArray()) {
        llvm::Function *callee = Function::Extract(info[0]);
        if (extractCalleeArgs(info[1].As<Napi::Array>(), calleeArgs)) {
            std::string name = argsLen >= 3 ? std::string(info[2].As<Napi::String>()) : "";
            call = builder->CreateCall(callee, calleeArgs, name);
        }
    } else if (argsLen >= 3 && FunctionType::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsArray()) {
        llvm::FunctionType *funcType = FunctionType::Extract(info[0]);
        llvm::Value *callee = Value::Extract(info[1]);
        if (extractCalleeArgs(info[1].As<Napi::Array>(), calleeArgs)) {
            std::string name = argsLen >= 3 ? std::string(info[3].As<Napi::String>()) : "";
            call = builder->CreateCall(funcType, callee, calleeArgs, name);
        }
    }
    if (call) {
        // TODO: opt here
        return Value::New(env, call);
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateCall needs to be called with: " \
    "(callee: Value, args: Value[], name?: string) or (funcType: FunctionType, callee: Value, args: Value[], name?: string)");
}

Napi::Value IRBuilder::createCondBr(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 3 && Value::IsClassOf(info[0]) && BasicBlock::IsClassOf(info[1]) && BasicBlock::IsClassOf(info[2])) {
        llvm::Value *cond = Value::Extract(info[0]);
        llvm::BasicBlock *thenBB = BasicBlock::Extract(info[1]);
        llvm::BasicBlock *elseBB = BasicBlock::Extract(info[2]);
        llvm::BranchInst *branch = builder->CreateCondBr(cond, thenBB, elseBB);
        // TODO: opt here
        return Value::New(env, branch);
    }
    throw Napi::TypeError::New(env, "IRBuilder.createCondBr needs to be called with: (cond: Value, thenBB: BasicBlock, elseBB: BasicBlock)");
}

Napi::Value IRBuilder::createLoad(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen == 2 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) ||
        argsLen >= 3 && Type::IsClassOf(info[0]) && Value::IsClassOf(info[1]) && info[2].IsString()) {
        llvm::Type *type = Type::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        std::string name = argsLen >= 2 ? std::string(info[2].As<Napi::String>()) : "";
        llvm::LoadInst *load = builder->CreateLoad(type, ptr, name);
        // TODO: opt here
        return Value::New(env, load);
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateLoad needs to be called with: (type: Type, ptr: Value, name?:string)");
}

Napi::Value IRBuilder::createRet(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argsLen = info.Length();
    if (argsLen >= 1 && Value::IsClassOf(info[0])) {
        // TODO: opt here
        return Value::New(env, builder->CreateRet(Value::Extract(info[0])));
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateRet needs to be called with: (value: Value)");
}

Napi::Value IRBuilder::createRetVoid(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    // TODO: opt here
    return Value::New(env, builder->CreateRetVoid());
}

Napi::Value IRBuilder::createStore(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && Value::IsClassOf(info[0]) && Value::IsClassOf(info[1])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::Value *ptr = Value::Extract(info[1]);
        llvm::StoreInst *store = builder->CreateStore(value, ptr);
        // TODO: opt here
        return Value::New(env, store);
    }
    throw Napi::TypeError::New(env, "IRBuilder.CreateStore needs to be called with: (value: Value, ptr: Value)");
}

Napi::Value IRBuilder::getInt1(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsBoolean()) {
        throw Napi::TypeError::New(env, "IRBuilder.getInt1 needs to be called with (value: boolean)");
    }
    bool value = info[0].As<Napi::Boolean>();
    return ConstantInt::New(env, builder->getInt1(value));
}

Napi::Value IRBuilder::getIntN(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, "IRBuilder.getIntN needs to be called with (n: number, value: number)");
    }
    unsigned n = info[0].As<Napi::Number>();
    uint64_t value = info[1].As<Napi::Number>().Int64Value();
    return ConstantInt::New(env, builder->getIntN(n, value));
}

Napi::Value IRBuilder::getInt(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !APInt::IsClassOf(info[0])) {
        throw Napi::TypeError::New(env, "IRBuilder.getInt needs to be called with (value: APInt)");
    }
    llvm::APInt &value = APInt::Extract(info[0]);
    return ConstantInt::New(env, builder->getInt(value));
}

Napi::Value IRBuilder::getIntNTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, "IRBuilder.getIntNTy needs to be called with (n: number)");
    }
    unsigned n = info[0].As<Napi::Number>();
    return IntegerType::New(env, builder->getIntNTy(n));
}

Napi::Value IRBuilder::getInt8PtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen >= 1 && !info[0].IsNumber()) {
        throw Napi::TypeError::New(env, "IRBuilder.getInt8PtrTy needs to be called with (addrSpace?: number)");
    }
    unsigned addrSpace = argsLen >= 1 ? info[0].As<Napi::Number>() : 0;
    llvm::PointerType *type = builder->getInt8PtrTy(addrSpace);
    return PointerType::New(env, type);
}

Napi::Value IRBuilder::getIntPtrTy(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int argsLen = info.Length();
    if (argsLen == 0 || !DataLayout::IsClassOf(info[0]) || argsLen >= 2 && !info[1].IsNumber()) {
        throw Napi::TypeError::New(env, "IRBuilder.getIntPtrTy needs to be called with (dl: DataLayout, addrSpace?: number)");
    }
    llvm::DataLayout &dl = DataLayout::Extract(info[0]);
    unsigned addrSpace = argsLen >= 2 ? info[1].As<Napi::Number>() : 0;
    llvm::IntegerType *type = builder->getIntPtrTy(dl, addrSpace);
    return IntegerType::New(env, type);
}


