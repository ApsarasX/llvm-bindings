import { BasicBlock, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('variable.cpp');
    const func = createFunction('test', builder.getVoidTy(), [], module);
    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);
    const alloca = builder.CreateAlloca(builder.getInt32Ty(), null, 'a');
    builder.CreateStore(builder.getInt32(11), alloca);

    const value = builder.CreateLoad(builder.getInt32Ty(), alloca);

    const cond = builder.CreateICmpSGT(value, builder.getInt32(10), 'cond');

    builder.CreateSelect(cond, builder.getInt32(10), builder.getInt32(20));

    builder.CreateRetVoid();

    if (verifyFunction(func)) {
        console.error('Verifying function failed');
        return;
    }
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}
