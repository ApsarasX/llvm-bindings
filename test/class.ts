import path from 'path';
import llvm from '..';

export default function testClass(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const elementTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const classStructType = llvm.StructType.create(context, elementTypes, 'Person');

    const returnType = builder.getVoidTy();
    const paramTypes = [llvm.PointerType.getUnqual(classStructType)];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'class_Person_constructor', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);

    const thisPtr = func.getArg(0);
    const propertyPtr = builder.CreateGEP(classStructType, thisPtr, [
        builder.getInt32(0),
        builder.getInt32(1)
    ]);
    builder.CreateStore(builder.getInt32(111), propertyPtr);
    builder.CreateRetVoid();

    console.log(module.print());

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'class_Person_constructor' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
};
