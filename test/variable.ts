import path from 'path';
import llvm from '..';

export default function testVariable(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const functionType = llvm.FunctionType.get(returnType, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'variable', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);
    const alloca = builder.CreateAlloca(builder.getInt32Ty(), null, 'a');
    builder.CreateStore(builder.getInt32(11), alloca);

    const value = builder.CreateLoad(builder.getInt32Ty(), alloca);

    const cond = builder.CreateICmpSGT(value, builder.getInt32(10), 'cond');

    builder.CreateSelect(cond, builder.getInt32(10), builder.getInt32(20));

    builder.CreateRetVoid();

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: 'verifying the function failed`);
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    module.print();
}
