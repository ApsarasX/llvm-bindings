import path from 'path';
import llvm from '..';

export default function testGEP(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getVoidTy();
    const functionType = llvm.FunctionType.get(returnType, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'gep', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);

    const strAlloca = builder.CreateAlloca(builder.getInt8PtrTy(), null, 'a');
    const printConst = builder.CreateGlobalString(
        'string content',
        '.str',
        0,
        module
    );
    const ptr = builder.CreateGEP(printConst.getValueType(), printConst, [
        builder.getInt64(0),
        builder.getInt64(0),
    ]);
    builder.CreateStore(ptr, strAlloca);

    builder.CreateRetVoid();

    console.log(module.print());

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: 'verifying the 'gep' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
}
