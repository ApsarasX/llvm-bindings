import path from 'path';
import llvm from '..';

export default function testSwitch(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty()];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'switch', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    const case1BB = llvm.BasicBlock.Create(context, 'switch.case1', func);
    const case2BB = llvm.BasicBlock.Create(context, 'switch.case2', func);
    const defaultCaseBB = llvm.BasicBlock.Create(context, 'switch.default', func);
    const exitBB = llvm.BasicBlock.Create(context, 'switch.exit', func);

    // entry
    builder.SetInsertPoint(entryBB);
    const retPtr = builder.CreateAlloca(builder.getInt32Ty(), null, 'ret');
    const switchInst = builder.CreateSwitch(func.getArg(0), defaultCaseBB, 2);
    switchInst.addCase(builder.getInt32(1), case1BB);
    switchInst.addCase(builder.getInt32(2), case2BB);

    // switch.case1
    builder.SetInsertPoint(case1BB);
    builder.CreateStore(builder.getInt32(1), retPtr);
    builder.CreateBr(exitBB);

    // switch.case2
    builder.SetInsertPoint(case2BB);
    builder.CreateStore(builder.getInt32(2), retPtr);
    builder.CreateBr(exitBB);

    // switch.default
    builder.SetInsertPoint(defaultCaseBB);
    builder.CreateStore(builder.getInt32(3), retPtr);
    builder.CreateBr(exitBB);

    // switch.exit
    builder.SetInsertPoint(exitBB);
    const retVal = builder.CreateLoad(builder.getInt32Ty(), retPtr);
    builder.CreateRet(retVal);

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'switch' function failed`);
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    module.print();
}
