import { BasicBlock, DebugLoc, DIBuilder, DILocation, Function, FunctionType, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('debug-info.cpp');
    module.addModuleFlag(2, "Debug Info Version", 3);
    module.addModuleFlag(2, "Dwarf Version", 4);
    const debugInfoBuilder = new DIBuilder(module);
    const debugInfoFile = debugInfoBuilder.createFile('debug-info.cpp', __dirname);
    const debugInfoUnit = debugInfoBuilder.createCompileUnit(0x0002, debugInfoFile, "llvm-bindings", false, "", 0);
    const debugInfoBasicType = debugInfoBuilder.createBasicType("int", 32, 0x05);

    const returnType = builder.getInt32Ty();
    const functionType = FunctionType.get(returnType, false);
    const mainFunc = Function.Create(functionType, Function.LinkageTypes.ExternalLinkage, 'main', module);
    const debugInfoParamTypes = debugInfoBuilder.getOrCreateTypeArray([debugInfoBasicType]);
    const debugInfoSubroutineType = debugInfoBuilder.createSubroutineType(debugInfoParamTypes);
    const debugInfoMainFuncSubprogram = debugInfoBuilder.createFunction(
        debugInfoUnit, 'main', '', debugInfoFile, 1,
        debugInfoSubroutineType, 1, 0, 1 << 3
    );

    mainFunc.setSubprogram(debugInfoMainFuncSubprogram);
    builder.SetCurrentDebugLocation(new DebugLoc());

    const entryBB = BasicBlock.Create(context, 'entry', mainFunc);
    builder.SetInsertPoint(entryBB);

    const allocaA = builder.CreateAlloca(builder.getInt32Ty(), null, "a");
    const allocaB = builder.CreateAlloca(builder.getInt32Ty(), null, "b");
    const allocaC = builder.CreateAlloca(builder.getInt32Ty(), null, "c");

    builder.SetCurrentDebugLocation(DILocation.get(context, 2, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(1), allocaA);

    builder.SetCurrentDebugLocation(DILocation.get(context, 3, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(2), allocaB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 4, 13, debugInfoMainFuncSubprogram));
    const loadA = builder.CreateLoad(builder.getInt32Ty(), allocaA);

    builder.SetCurrentDebugLocation(DILocation.get(context, 4, 17, debugInfoMainFuncSubprogram));
    const loadB = builder.CreateLoad(builder.getInt32Ty(), allocaB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 4, 15, debugInfoMainFuncSubprogram));
    const value = builder.CreateAdd(loadA, loadB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 4, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(value, allocaC);

    builder.SetCurrentDebugLocation(DILocation.get(context, 5, 12, debugInfoMainFuncSubprogram));
    const loadC = builder.CreateLoad(builder.getInt32Ty(), allocaC);

    builder.SetCurrentDebugLocation(DILocation.get(context, 5, 5, debugInfoMainFuncSubprogram));
    builder.CreateRet(loadC);

    debugInfoBuilder.finalizeSubprogram(debugInfoMainFuncSubprogram);
    if (verifyFunction(mainFunc)) {
        console.error('Verifying function failed');
        return;
    }
    debugInfoBuilder.finalize();
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}
