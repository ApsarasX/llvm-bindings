import path from 'path';
import { SMDiagnostic, Linker, parseIRFile, verifyModule, BasicBlock, verifyFunction } from '..';
import { createFunction, getContextModuleBuilder } from "./util";

export default function (): void {
    const filename = path.join(__dirname, 'bitcode/add.bc');
    const { context, module, builder } = getContextModuleBuilder('linker.cpp');
    const err = new SMDiagnostic();
    const srcModule = parseIRFile(filename, err, context);
    if (verifyModule(srcModule)) {
        console.error('Verifying src module failed');
        return;
    }
    if (Linker.linkModules(module, srcModule)) {
        console.error('Linking modules failed');
        return;
    }
    const func = createFunction('link', builder.getInt32Ty(), [], module);
    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertionPoint(entryBB);
    const addFunc = module.getFunction('add');
    if (!addFunc) {
        console.error('Unable to find the `add` function');
        return;
    }
    const argA = builder.getInt32(1);
    const argB = builder.getInt32(2);
    const retVal = builder.CreateCall(addFunc, [argA, argB]);
    builder.CreateRet(retVal);

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
