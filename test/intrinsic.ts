import { BasicBlock, Intrinsic, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('intrinsic.cpp');
    const func = createFunction('main', builder.getVoidTy(), [], module);

    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertionPoint(entryBB);
    const debugtrapFn = Intrinsic.getDeclaration(module, Intrinsic.debugtrap);
    builder.CreateCall(debugtrapFn, []);
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
