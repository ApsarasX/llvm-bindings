import path from 'path';
import llvm from '..';

export default function testFibonacci(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty()];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'fibonacci', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    const thenBB = llvm.BasicBlock.Create(context, 'then', func);
    const elseBB = llvm.BasicBlock.Create(context, 'else', func);

    builder.SetInsertPoint(entryBB);
    const cond = builder.CreateICmpULE(func.getArg(0), builder.getInt32(1), 'cond');
    builder.CreateCondBr(cond, thenBB, elseBB);

    builder.SetInsertPoint(thenBB);
    builder.CreateRet(func.getArg(0));

    builder.SetInsertPoint(elseBB);
    const n_1 = builder.CreateSub(func.getArg(0), builder.getInt32(1), 'n_1');
    const n_2 = builder.CreateSub(func.getArg(0), builder.getInt32(2), 'n_2');
    const ret1 = builder.CreateCall(func, [n_1], 'ret1');
    const ret2 = builder.CreateCall(func, [n_2], 'ret2');
    const result = builder.CreateAdd(ret1, ret2);
    builder.CreateRet(result);

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'fibonacci' function failed`);
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    module.print();
}
