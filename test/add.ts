import path from 'path';
import llvm from '..';

export default function testAdd(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'add', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry');
    builder.SetInsertPoint(entryBB);
    const paramA = func.getArg(0);
    const paramB = func.getArg(1);
    const result = builder.CreateAdd(paramA, paramB);
    builder.CreateRet(result);

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'add' function failed`);
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    console.log(module.print());
}
