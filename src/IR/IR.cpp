#include "IR/IR.h"

void InitIR(Napi::Env env, Napi::Object &exports) {
    LLVMContext::Init(env, exports);
    Module::Init(env, exports);
    Type::Init(env, exports);
    IntegerType::Init(env, exports);
    PointerType::Init(env, exports);
    FunctionType::Init(env, exports);
    StructType::Init(env, exports);
    ArrayType::Init(env, exports);
    Value::Init(env, exports);
    User::Init(env, exports);
    Instruction::Init(env, exports);
    AllocaInst::Init(env, exports);
    BranchInst::Init(env, exports);
    CallInst::Init(env, exports);
    LoadInst::Init(env, exports);
    ReturnInst::Init(env, exports);
    StoreInst::Init(env, exports);
    PHINode::Init(env, exports);
    Constant::Init(env, exports);
    ConstantInt::Init(env, exports);
    ConstantFP::Init(env, exports);
    ConstantPointerNull::Init(env, exports);
    ConstantStruct::Init(env, exports);
    GlobalValue::Init(env, exports);
    GlobalObject::Init(env, exports);
    GlobalVariable::Init(env, exports);
    Function::Init(env, exports);
    Argument::Init(env, exports);
    BasicBlock::Init(env, exports);
    IRBuilder::Init(env, exports);
    DataLayout::Init(env, exports);
    InitVerifier(env, exports);
}