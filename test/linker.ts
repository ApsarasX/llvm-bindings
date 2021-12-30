import path from 'path';
import llvm from '..';

export default function testLinker(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const bitcodePath = path.join(__dirname, 'bitcode/add.bc');
    const err = new llvm.SMDiagnostic();
    const srcModule = llvm.parseIRFile(bitcodePath, err, context);
    if (llvm.verifyModule(srcModule)) {
        console.error(`${filename}: verifying the source module failed`);
        return;
    }
    if (llvm.Linker.linkModules(module, srcModule)) {
        console.error(`${filename}: linking the source modules to the destination module failed`);
        return;
    }

    const returnType = builder.getInt32Ty();
    const functionType = llvm.FunctionType.get(returnType, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'linker', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);
    const addFunc = module.getFunction('add');
    if (!addFunc) {
        console.error(`${filename}: unable to get the 'add' function`);
        return;
    }
    const argA = builder.getInt32(1);
    const argB = builder.getInt32(2);
    const retVal = builder.CreateCall(addFunc, [argA, argB]);
    builder.CreateRet(retVal);

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'linker' function failed`);
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    console.log(module.print());
}
