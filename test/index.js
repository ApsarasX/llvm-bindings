const {
    BasicBlock,
    LLVMContext,
    Module,
    ConstantInt,
    IntegerType,
    FunctionType,
    Function,
    IRBuilder,
    verifyModule
} = require('..');

const ctx = new LLVMContext();

const mod = new Module("main.cpp", ctx);

const builder = new IRBuilder(ctx);

const int32Ty = IntegerType.get(ctx, 32);

const funcType = FunctionType.get(int32Ty, false);

const func = Function.Create(funcType, Function.LinkageTypes.ExternalLinkage, "main", mod);

const entryBB = BasicBlock.Create(ctx, "entry", func);

builder.SetInsertionPoint(entryBB);

const a = ConstantInt.get(int32Ty, 200);

const b = ConstantInt.get(int32Ty, 500);

const c = builder.CreateAdd(a, b, "c");

builder.CreateRet(c);

if (!verifyModule(mod)) {
    mod.print();
}