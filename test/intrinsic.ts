import path from 'path';
import llvm from '..';

export default function testIntrinsic(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getVoidTy();
    const functionType = llvm.FunctionType.get(returnType, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'intrinsic', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);
    const debugtrapFn = llvm.Intrinsic.getDeclaration(module, llvm.Intrinsic.debugtrap);
    builder.CreateCall(debugtrapFn, []);
    const memmoveFn = llvm.Intrinsic.getDeclaration(module, llvm.Intrinsic.memmove, [
        builder.getInt8PtrTy(),
        builder.getInt8PtrTy(),
        builder.getInt32Ty()
    ]);
    builder.CreateRetVoid();

    console.log(module.print());

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'intrinsic' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
}
