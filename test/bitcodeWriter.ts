import fs from 'fs';
import path from 'path';
import llvm from '..';

export default function testBitcodeWriter(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'writer', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry');
    builder.SetInsertPoint(entryBB);
    const paramA = func.getArg(0);
    const paramB = func.getArg(1);
    const result = builder.CreateAdd(paramA, paramB);
    builder.CreateRet(result);

    console.log(module.print());

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'writer' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }

    const outputDir = path.join(__dirname, 'temp');
    const outputBitcodePath = path.join(outputDir, 'add.out.bc');
    if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir);
    }
    if (fs.existsSync(outputBitcodePath)) {
        fs.unlinkSync(outputBitcodePath);
    }
    llvm.WriteBitcodeToFile(module, outputBitcodePath);
    console.log(`${filename}: bitcode was successfully written to the ${outputBitcodePath}`);
}
