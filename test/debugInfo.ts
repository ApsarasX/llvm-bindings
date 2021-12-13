import {
    BasicBlock,
    DebugLoc,
    DIBasicType,
    DIBuilder,
    DICompileUnit,
    DIFile,
    DILocation,
    DISubprogram,
    Function,
    FunctionType,
    IRBuilder,
    LLVMContext,
    Module,
    dwarf,
    verifyFunction,
    verifyModule, DINode
} from '..';
import { getContextModuleBuilder } from './util';

function createAddFunc(
    context: LLVMContext,
    module: Module,
    builder: IRBuilder,
    debugInfoBuilder: DIBuilder,
    debugInfoFile: DIFile,
    debugInfoUnit: DICompileUnit,
    debugInfoBasicType: DIBasicType): Function {

    const addFuncReturnType = builder.getInt32Ty();
    const addFuncParamTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const addFuncType = FunctionType.get(addFuncReturnType, addFuncParamTypes, false);
    const addFunc = Function.Create(addFuncType, Function.LinkageTypes.ExternalLinkage, 'add', module);
    const debugInfoParamTypes = debugInfoBuilder.getOrCreateTypeArray([debugInfoBasicType, debugInfoBasicType, debugInfoBasicType]);
    const debugInfoSubroutineType = debugInfoBuilder.createSubroutineType(debugInfoParamTypes);
    const debugInfoAddFuncSubprogram = debugInfoBuilder.createFunction(
        debugInfoFile, 'add', '', debugInfoFile, 1,
        debugInfoSubroutineType, 1, DINode.DIFlags.FlagPrototyped, DISubprogram.DISPFlags.SPFlagDefinition
    );

    addFunc.setSubprogram(debugInfoAddFuncSubprogram);
    builder.SetCurrentDebugLocation(new DebugLoc());

    const entryBB = BasicBlock.Create(context, 'entry', addFunc);
    builder.SetInsertPoint(entryBB);

    const allocaA = builder.CreateAlloca(builder.getInt32Ty(), null, 'a');
    builder.CreateStore(addFunc.getArg(0), allocaA);
    const diLocalVarA = debugInfoBuilder.createParameterVariable(debugInfoAddFuncSubprogram, 'a', 0, debugInfoFile, 1, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaA,
        diLocalVarA,
        debugInfoBuilder.createExpression(),
        DILocation.get(context, 1, 0, debugInfoAddFuncSubprogram),
        builder.GetInsertBlock()
    );


    const allocaB = builder.CreateAlloca(builder.getInt32Ty(), null, 'b');
    builder.CreateStore(addFunc.getArg(1), allocaB);
    const diLocalVarB = debugInfoBuilder.createParameterVariable(debugInfoAddFuncSubprogram, 'b', 1, debugInfoFile, 1, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaB,
        diLocalVarB,
        debugInfoBuilder.createExpression(),
        DILocation.get(context, 1, 0, debugInfoAddFuncSubprogram),
        builder.GetInsertBlock()
    );

    builder.SetCurrentDebugLocation(DILocation.get(context, 2, 12, debugInfoAddFuncSubprogram));
    const loadA = builder.CreateLoad(builder.getInt32Ty(), allocaA);

    builder.SetCurrentDebugLocation(DILocation.get(context, 2, 16, debugInfoAddFuncSubprogram));
    const loadB = builder.CreateLoad(builder.getInt32Ty(), allocaB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 2, 14, debugInfoAddFuncSubprogram));
    const value = builder.CreateAdd(loadA, loadB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 2, 5, debugInfoAddFuncSubprogram));
    builder.CreateRet(value);

    debugInfoBuilder.finalizeSubprogram(debugInfoAddFuncSubprogram);
    if (verifyFunction(addFunc)) {
        console.error('Verifying function failed');
    }
    return addFunc;
}

function createMainFunc(
    context: LLVMContext,
    module: Module,
    builder: IRBuilder,
    debugInfoBuilder: DIBuilder,
    debugInfoFile: DIFile,
    debugInfoUnit: DICompileUnit,
    debugInfoBasicType: DIBasicType,
    addFunc: Function): Function {

    const mainFuncReturnType = builder.getInt32Ty();
    const mainFuncType = FunctionType.get(mainFuncReturnType, false);
    const mainFunc = Function.Create(mainFuncType, Function.LinkageTypes.ExternalLinkage, 'main', module);
    const debugInfoParamTypes = debugInfoBuilder.getOrCreateTypeArray([debugInfoBasicType]);
    const debugInfoSubroutineType = debugInfoBuilder.createSubroutineType(debugInfoParamTypes);
    const debugInfoMainFuncSubprogram = debugInfoBuilder.createFunction(
        debugInfoFile, 'main', '', debugInfoFile, 5,
        debugInfoSubroutineType, 5, DINode.DIFlags.FlagPrototyped, DISubprogram.DISPFlags.SPFlagDefinition
    );

    mainFunc.setSubprogram(debugInfoMainFuncSubprogram);
    builder.SetCurrentDebugLocation(new DebugLoc());

    const entryBB = BasicBlock.Create(context, 'entry', mainFunc);
    builder.SetInsertPoint(entryBB);

    const allocaA = builder.CreateAlloca(builder.getInt32Ty(), null, "a");
    const allocaB = builder.CreateAlloca(builder.getInt32Ty(), null, "b");
    const allocaC = builder.CreateAlloca(builder.getInt32Ty(), null, "c");

    const diLocalVarA = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'a', debugInfoFile, 6, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaA,
        diLocalVarA,
        debugInfoBuilder.createExpression(),
        DILocation.get(context, 6, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()
    );
    builder.SetCurrentDebugLocation(DILocation.get(context, 6, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(1), allocaA);

    const diLocalVarB = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'b', debugInfoFile, 7, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaB,
        diLocalVarB,
        debugInfoBuilder.createExpression(),
        DILocation.get(context, 7, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()
    );
    builder.SetCurrentDebugLocation(DILocation.get(context, 7, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(builder.getInt32(2), allocaB);

    const diLocalVarC = debugInfoBuilder.createAutoVariable(debugInfoMainFuncSubprogram, 'c', debugInfoFile, 8, debugInfoBasicType);
    debugInfoBuilder.insertDeclare(
        allocaC,
        diLocalVarC,
        debugInfoBuilder.createExpression(),
        DILocation.get(context, 8, 9, debugInfoMainFuncSubprogram),
        builder.GetInsertBlock()
    );

    builder.SetCurrentDebugLocation(DILocation.get(context, 8, 17, debugInfoMainFuncSubprogram));
    const loadA = builder.CreateLoad(builder.getInt32Ty(), allocaA);

    builder.SetCurrentDebugLocation(DILocation.get(context, 8, 20, debugInfoMainFuncSubprogram));
    const loadB = builder.CreateLoad(builder.getInt32Ty(), allocaB);

    builder.SetCurrentDebugLocation(DILocation.get(context, 8, 13, debugInfoMainFuncSubprogram));
    const callRet = builder.CreateCall(addFunc, [loadA, loadB]);

    builder.SetCurrentDebugLocation(DILocation.get(context, 8, 9, debugInfoMainFuncSubprogram));
    builder.CreateStore(callRet, allocaC);

    builder.SetCurrentDebugLocation(DILocation.get(context, 9, 12, debugInfoMainFuncSubprogram));
    const loadC = builder.CreateLoad(builder.getInt32Ty(), allocaC);

    builder.SetCurrentDebugLocation(DILocation.get(context, 9, 5, debugInfoMainFuncSubprogram));
    builder.CreateRet(loadC);

    debugInfoBuilder.finalizeSubprogram(debugInfoMainFuncSubprogram);
    if (verifyFunction(mainFunc)) {
        console.error('Verifying function failed');
    }
    return mainFunc;
}

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('debug-info.cpp');
    module.addModuleFlag(2, "Debug Info Version", 3);
    module.addModuleFlag(2, "Dwarf Version", 4);
    const debugInfoBuilder = new DIBuilder(module);
    const debugInfoFile = debugInfoBuilder.createFile('debug-info.cpp', __dirname);
    const debugInfoUnit = debugInfoBuilder.createCompileUnit(dwarf.SourceLanguage.DW_LANG_C, debugInfoFile, "llvm-bindings", false, "", 0);
    const debugInfoBasicType = debugInfoBuilder.createBasicType("int", 32, dwarf.TypeKind.DW_ATE_float);

    const addFunc = createAddFunc(context, module, builder, debugInfoBuilder, debugInfoFile, debugInfoUnit, debugInfoBasicType);
    createMainFunc(context, module, builder, debugInfoBuilder, debugInfoFile, debugInfoUnit, debugInfoBasicType, addFunc);


    debugInfoBuilder.finalize();
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}
