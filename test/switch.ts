import { BasicBlock, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('switch.cpp');
    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty()];
    const func = createFunction('process', returnType, paramTypes, module);

    const entryBB = BasicBlock.Create(context, 'entry', func);
    const case1BB = BasicBlock.Create(context, 'switch.case1', func);
    const case2BB = BasicBlock.Create(context, 'switch.case2', func);
    const defaultCaseBB = BasicBlock.Create(context, 'switch.default', func);
    const exitBB = BasicBlock.Create(context, 'switch.exit', func);

    // entry
    builder.SetInsertionPoint(entryBB);
    const retPtr = builder.CreateAlloca(builder.getInt32Ty(), null, 'ret');
    const switchInst = builder.CreateSwitch(func.getArg(0), defaultCaseBB, 2);
    switchInst.addCase(builder.getInt32(1), case1BB);
    switchInst.addCase(builder.getInt32(2), case2BB);

    // switch.case1
    builder.SetInsertionPoint(case1BB);
    builder.CreateStore(builder.getInt32(1), retPtr);
    builder.CreateBr(exitBB);

    // switch.case2
    builder.SetInsertionPoint(case2BB);
    builder.CreateStore(builder.getInt32(2), retPtr);
    builder.CreateBr(exitBB);

    // switch.default
    builder.SetInsertionPoint(defaultCaseBB);
    builder.CreateStore(builder.getInt32(3), retPtr);
    builder.CreateBr(exitBB);

    // switch.exit
    builder.SetInsertionPoint(exitBB);
    const retVal = builder.CreateLoad(builder.getInt32Ty(), retPtr);
    builder.CreateRet(retVal);

    if (!verifyFunction(func) && !verifyModule(module)) {
        module.print();
    }
}
