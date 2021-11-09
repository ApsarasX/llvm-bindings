import { BasicBlock, Intrinsic, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('intrinsic.cpp');
    const func = createFunction('main', builder.getVoidTy(), [], module);

    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);
    const debugtrapFn = Intrinsic.getDeclaration(module, Intrinsic.debugtrap);
    builder.CreateCall(debugtrapFn, []);
    const memmoveFn = Intrinsic.getDeclaration(module, Intrinsic.memmove, [
        builder.getInt8PtrTy(),
        builder.getInt8PtrTy(),
        builder.getInt32Ty()
    ]);
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
