import { BasicBlock, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('fibonacci.cpp');
    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty()];
    const func = createFunction('fibonacci', returnType, paramTypes, module);

    const entryBB = BasicBlock.Create(context, 'entry', func);
    const thenBB = BasicBlock.Create(context, 'then', func);
    const elseBB = BasicBlock.Create(context, 'else', func);

    builder.SetInsertionPoint(entryBB);
    const cond = builder.CreateICmpULE(func.getArg(0), builder.getInt32(1), 'cond');
    builder.CreateCondBr(cond, thenBB, elseBB);

    builder.SetInsertionPoint(thenBB);
    builder.CreateRet(func.getArg(0));

    builder.SetInsertionPoint(elseBB);
    const n_1 = builder.CreateSub(func.getArg(0), builder.getInt32(1), 'n_1');
    const n_2 = builder.CreateSub(func.getArg(0), builder.getInt32(2), 'n_2');
    const ret1 = builder.CreateCall(func, [n_1], 'ret1');
    const ret2 = builder.CreateCall(func, [n_2], 'ret2');
    const result = builder.CreateAdd(ret1, ret2);
    builder.CreateRet(result);

    if (!verifyFunction(func) && !verifyModule(module)) {
        module.print();
    }
}
