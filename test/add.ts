import { BasicBlock, Module, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (toPrint: boolean = true): Module | null {
    const { context, module, builder } = getContextModuleBuilder('add.cpp');
    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const func = createFunction('add', returnType, paramTypes, module);

    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertionPoint(entryBB);
    const a = func.getArg(0);
    const b = func.getArg(1);
    const result = builder.CreateAdd(a, b);
    builder.CreateRet(result);
    
    if (verifyFunction(func)) {
        console.error('Verifying function failed');
        return null;
    }
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return null;
    }
    if (toPrint) {
        module.print();
    }
    return module;
}
