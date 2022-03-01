import path from 'path';
import llvm from '..';

function createAddFunc(
    context: llvm.LLVMContext,
    module: llvm.Module,
    builder: llvm.IRBuilder,
    debugInfoBuilder: llvm.DIBuilder,
    debugInfoFile: llvm.DIFile,
    debugInfoUnit: llvm.DICompileUnit,
    debugInfoBasicType: llvm.DIBasicType): llvm.Function {

    const addFuncReturnType = builder.getInt32Ty();
    const addFuncParamTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const addFuncType = llvm.FunctionType.get(addFuncReturnType, addFuncParamTypes, false);
    const addFunc = llvm.Function.Create(addFuncType, llvm.Function.LinkageTypes.ExternalLinkage, 'add', module);
    const debugInfoParamTypes = debugInfoBuilder.getOrCreateTypeArray([debugInfoBasicType, debugInfoBasicType, debugInfoBasicType]);
    const debugInfoSubroutineType = debugInfoBuilder.createSubroutineType(debugInfoParamTypes);
    const debugInfoAddFuncSubprogram = debugInfoBuilder.createFunction(
        debugInfoFile, 'add', '', debugInfoFile, 1,
        debugInfoSubroutineType, 1, llvm.DINode.DIFlags.FlagPrototyped, llvm.DISubprogram.DISPFlags.SPFlagDefinition
    );

    addFunc.setSubprogram(debugInfoAddFuncSubprogram);
    builder.SetCurrentDebugLocation(new llvm.DebugLoc());

    const entryBB = llvm.BasicBlock.Create(context, 'entry', addFunc);
    builder.SetInsertPoint(entryBB);

    const allocaA = builder.CreateAlloca(builder.getInt32Ty(), null, 'a');
    builder.CreateStore(addFunc.getArg(0), allocaA);
    const diLocalVarA = debugInfoBuilder.createParameterVariable(debugInfoAddFuncSubprogram, 'a', 1, debugInfoFile, 1, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaA,
        diLocalVarA,
        debugInfoBuilder.createExpression(),
        llvm.DILocation.get(context, 1, 0, debugInfoAddFuncSubprogram),
        builder.GetInsertBlock()!
    );

    const allocaB = builder.CreateAlloca(builder.getInt32Ty(), null, 'b');
    builder.CreateStore(addFunc.getArg(1), allocaB);
    const diLocalVarB = debugInfoBuilder.createParameterVariable(debugInfoAddFuncSubprogram, 'b', 2, debugInfoFile, 1, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaB,
        diLocalVarB,
        debugInfoBuilder.createExpression(),
        llvm.DILocation.get(context, 1, 0, debugInfoAddFuncSubprogram),
        builder.GetInsertBlock()!
    );

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 2, 12, debugInfoAddFuncSubprogram));
    const loadA = builder.CreateLoad(builder.getInt32Ty(), allocaA);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 2, 16, debugInfoAddFuncSubprogram));
    const loadB = builder.CreateLoad(builder.getInt32Ty(), allocaB);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 2, 14, debugInfoAddFuncSubprogram));
    const value = builder.CreateAdd(loadA, loadB);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 2, 5, debugInfoAddFuncSubprogram));
    builder.CreateRet(value);

    debugInfoBuilder.finalizeSubprogram(debugInfoAddFuncSubprogram);
    if (llvm.verifyFunction(addFunc)) {
        console.error(`${path.basename(__filename)}: verifying the 'add' function failed`);
    }
    return addFunc;
}

function createMainFunc(
    context: llvm.LLVMContext,
    module: llvm.Module,
    builder: llvm.IRBuilder,
    debugInfoBuilder: llvm.DIBuilder,
    debugInfoFile: llvm.DIFile,
    debugInfoUnit: llvm.DICompileUnit,
    debugInfoBasicType: llvm.DIBasicType,
    addFunc: llvm.Function): llvm.Function {

    const mainFuncReturnType = builder.getInt32Ty();
    const mainFuncType = llvm.FunctionType.get(mainFuncReturnType, false);
    const mainFunc = llvm.Function.Create(mainFuncType, llvm.Function.LinkageTypes.ExternalLinkage, 'main', module);
    const debugInfoParamTypes = debugInfoBuilder.getOrCreateTypeArray([debugInfoBasicType]);
    const debugInfoSubroutineType = debugInfoBuilder.createSubroutineType(debugInfoParamTypes);
    const debugInfoMainFuncSubprogram = debugInfoBuilder.createFunction(
        debugInfoFile, 'main', '', debugInfoFile, 5,
        debugInfoSubroutineType, 5, llvm.DINode.DIFlags.FlagPrototyped, llvm.DISubprogram.DISPFlags.SPFlagDefinition
    );

    mainFunc.setSubprogram(debugInfoMainFuncSubprogram);
    builder.SetCurrentDebugLocation(new llvm.DebugLoc());

    const entryBB = llvm.BasicBlock.Create(context, 'entry', mainFunc);
    builder.SetInsertPoint(entryBB);

    const allocaA = builder.CreateAlloca(builder.getInt32Ty(), null, 'a');
    const allocaB = builder.CreateAlloca(builder.getInt32Ty(), null, 'b');
    const allocaC = builder.CreateAlloca(builder.getInt32Ty(), null, 'c');

    const diLocalVarA = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'a', debugInfoFile, 6, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaA,
        diLocalVarA,
        debugInfoBuilder.createExpression(),
        llvm.DILocation.get(context, 6, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()!
    );
    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 6, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(1), allocaA);

    const diLocalVarB = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'b', debugInfoFile, 7, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaB,
        diLocalVarB,
        debugInfoBuilder.createExpression(),
        llvm.DILocation.get(context, 7, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()!
    );
    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 7, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(2), allocaB);

    const diLocalVarC = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'c', debugInfoFile, 8, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaC,
        diLocalVarC,
        debugInfoBuilder.createExpression(),
        llvm.DILocation.get(context, 8, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()!
    );

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 8, 17, debugInfoMainFuncSubprogram));
    const loadA = builder.CreateLoad(builder.getInt32Ty(), allocaA);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 8, 20, debugInfoMainFuncSubprogram));
    const loadB = builder.CreateLoad(builder.getInt32Ty(), allocaB);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 8, 13, debugInfoMainFuncSubprogram));
    const callRet = builder.CreateCall(addFunc, [loadA, loadB]);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 8, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(callRet, allocaC);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 9, 12, debugInfoMainFuncSubprogram));
    const loadC = builder.CreateLoad(builder.getInt32Ty(), allocaC);

    builder.SetCurrentDebugLocation(llvm.DILocation.get(context, 9, 5, debugInfoMainFuncSubprogram));
    builder.CreateRet(loadC);

    debugInfoBuilder.finalizeSubprogram(debugInfoMainFuncSubprogram);
    if (llvm.verifyFunction(mainFunc)) {
        console.error(`${path.basename(__filename)}: verifying the 'main' function failed`);
    }
    return mainFunc;
}

export default function testDebugInfo(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    module.addModuleFlag(llvm.Module.ModFlagBehavior.Warning, 'Debug Info Version', llvm.LLVMConstants.DEBUG_METADATA_VERSION);
    module.addModuleFlag(llvm.Module.ModFlagBehavior.Warning, 'Dwarf Version', llvm.dwarf.LLVMConstants.DWARF_VERSION);
    const debugInfoBuilder = new llvm.DIBuilder(module);
    const debugInfoFile = debugInfoBuilder.createFile(path.basename(__filename), __dirname);
    const debugInfoUnit = debugInfoBuilder.createCompileUnit(llvm.dwarf.SourceLanguage.DW_LANG_C, debugInfoFile, 'llvm-bindings', false, '', 0);
    const debugInfoBasicType = debugInfoBuilder.createBasicType('int', 32, llvm.dwarf.TypeKind.DW_ATE_float);

    const addFunc = createAddFunc(context, module, builder, debugInfoBuilder, debugInfoFile, debugInfoUnit, debugInfoBasicType);
    createMainFunc(context, module, builder, debugInfoBuilder, debugInfoFile, debugInfoUnit, debugInfoBasicType, addFunc);

    debugInfoBuilder.finalize();
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        return;
    }
    console.log(module.print());
}
