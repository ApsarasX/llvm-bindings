import path from 'path';
import llvm from '../..';

const FileName = path.basename(__filename);

describe('Test Module', () => {
    describe('Test llvm.Module.constructor', () => {
        const constructorErrMsg =
            'Module.constructor needs to be called with' +
            '\n\t - new (external: Napi::External<llvm::Module>)' +
            '\n\t - new (moduleID: string, context: LLVMContext)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module).toBeInstanceOf(llvm.Module);
        });

        test('Test Without Enough Arguments', () => {
            const ModuleCtor = llvm.Module as any;
            expect(() => new ModuleCtor()).toThrowError(constructorErrMsg);
            expect(() => new ModuleCtor(FileName)).toThrowError(constructorErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            const ModuleCtor = llvm.Module as any;
            expect(() => new ModuleCtor(1, new llvm.LLVMContext())).toThrowError(constructorErrMsg);
            expect(() => new ModuleCtor(FileName, {})).toThrowError(constructorErrMsg);
        });
    });

    describe('Test llvm.Module.get/setModuleIdentifier', () => {
        const setMoudleIDErrMsg = 'Module.setModuleIdentifier needs to be called with: (moduleID: string)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getModuleIdentifier()).toEqual(FileName);
            module.setModuleIdentifier('module');
            expect(module.getModuleIdentifier()).toEqual('module');
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setModuleIdentifier = module.setModuleIdentifier.bind(module) as any;
                setModuleIdentifier();
            }).toThrowError(setMoudleIDErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setModuleIdentifier = module.setModuleIdentifier.bind(module) as any;
                setModuleIdentifier(1);
            }).toThrowError(setMoudleIDErrMsg);
        });
    });

    describe('Test llvm.Module.get/setSourceFileName', () => {
        const setSourceFileNameErrMsg = 'Module.setSourceFileName needs to be called with: (sourceFileName: string)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getSourceFileName()).toEqual(FileName);
            module.setSourceFileName('test.cpp');
            expect(module.getSourceFileName()).toEqual('test.cpp');
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setSourceFileName = module.setSourceFileName.bind(module) as any;
                setSourceFileName();
            }).toThrowError(setSourceFileNameErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setSourceFileName = module.setSourceFileName.bind(module) as any;
                setSourceFileName(1);
            }).toThrowError(setSourceFileNameErrMsg);
        });
    });

    test('Test llvm.Module.getName', () => {
        const context = new llvm.LLVMContext();
        const module = new llvm.Module(FileName, context);
        expect(module.getName()).toEqual(FileName);
    });

    describe('Test llvm.Module.get/setDataLayout', () => {
        const datalayout = 'e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128';
        const setDataLayoutErrMsg =
            'Module.setDataLayout needs to be called with:' +
            '\n\t - (desc: string)' +
            '\n\t - (dataLayout: DataLayout)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getDataLayoutStr()).toEqual('');
            module.setDataLayout(datalayout);
            expect(module.getDataLayoutStr()).toEqual(datalayout);
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setDataLayout = module.setDataLayout.bind(module) as any;
                setDataLayout();
            }).toThrowError(setDataLayoutErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setDataLayout = module.setDataLayout.bind(module) as any;
                setDataLayout(1);
            }).toThrowError(setDataLayoutErrMsg);
        });
    });

    describe('Test llvm.Module.get/setTargetTriple', () => {
        const setTargetTripleErrMsg = 'Module.setTargetTriple needs to be called with: (targetTriple: string)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getTargetTriple()).toEqual('');
            const targetTriple = 'x86_64-pc-linux-gnu';
            module.setTargetTriple(targetTriple);
            expect(module.getTargetTriple()).toEqual(targetTriple);
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setTargetTriple = module.setTargetTriple.bind(module) as any;
                setTargetTriple();
            }).toThrowError(setTargetTripleErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const setTargetTriple = module.setTargetTriple.bind(module) as any;
                setTargetTriple(1);
            }).toThrowError(setTargetTripleErrMsg);
        });
    });

    describe('Test llvm.Module.getOrInsertFunction', () => {
        const getOrInsertFunctionErrMsg = 'Module.getOrInsertFunction needs to be called with: (name: string, fnType: FunctionType)';

        test('Test If No Such Function Exists', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            const funcCallee = module.getOrInsertFunction('func', funcType);
            const resultFunc = module.getFunction('func');
            const resultFuncType = funcCallee.getFunctionType();
            expect(funcCallee).toBeInstanceOf(llvm.FunctionCallee);
            expect(resultFunc).toBeInstanceOf(llvm.Function);
            expect(resultFuncType).toBeInstanceOf(llvm.FunctionType);
        });

        test('Test If Such Function Exists', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            const func = llvm.Function.Create(funcType, llvm.Function.LinkageTypes.ExternalLinkage, 'func', module);
            const funcCallee = module.getOrInsertFunction('func', llvm.FunctionType.get(llvm.Type.getVoidTy(context), false));
            const resultFunc = module.getFunction('func');
            const resultFuncType = funcCallee.getFunctionType();
            expect(funcCallee).toBeInstanceOf(llvm.FunctionCallee);
            expect(resultFunc).toBeInstanceOf(llvm.Function);
            expect(resultFuncType).toBeInstanceOf(llvm.FunctionType);
        });

        test('Test Without Enough Arguments', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const getOrInsertFunction = module.getOrInsertFunction.bind(module) as any;
            expect(() => getOrInsertFunction()).toThrowError(getOrInsertFunctionErrMsg);
            expect(() => getOrInsertFunction('func')).toThrowError(getOrInsertFunctionErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            const getOrInsertFunction = module.getOrInsertFunction.bind(module) as any;
            expect(() => getOrInsertFunction(1, funcType)).toThrowError(getOrInsertFunctionErrMsg);
            expect(() => getOrInsertFunction('func', 1)).toThrowError(getOrInsertFunctionErrMsg);
            expect(() => getOrInsertFunction(1, 1)).toThrowError(getOrInsertFunctionErrMsg);
        });
    });

    describe('Test llvm.Module.getFunction', () => {
        const getFunctionErrMsg = 'Module.getFunction needs to be called with: (name: string)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            const func = llvm.Function.Create(funcType, llvm.Function.LinkageTypes.ExternalLinkage, 'func', module);
            expect(module.getFunction('func')).toEqual(func);
        });

        test('Test If No Such Function Exists', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getFunction('func')).toBeNull();
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const getFunction = module.getFunction.bind(module) as any;
                getFunction();
            }).toThrowError(getFunctionErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const getFunction = module.getFunction.bind(module) as any;
                getFunction(1);
            }).toThrowError(getFunctionErrMsg);
        });
    });

    describe('Test llvm.Module.getGlobalVariable', () => {
        const getGlobalVariableErrMsg = 'Module.getGlobalVariable needs to be called with: (name: string, allowInternal?: boolean)';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const constantType = llvm.Type.getInt32Ty(context);
            const constant = llvm.ConstantInt.get(constantType, 23);
            new llvm.GlobalVariable(module, constantType, true, llvm.Function.LinkageTypes.ExternalLinkage, constant, 'globalVar');
            expect(module.getGlobalVariable('globalVar')).toBeInstanceOf(llvm.GlobalVariable);
        });

        test('Test If No Such Global Variable Exists', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.getGlobalVariable('globalVar')).toBeNull();
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const getGlobalVariable = module.getGlobalVariable.bind(module) as any;
                getGlobalVariable();
            }).toThrowError(getGlobalVariableErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const getGlobalVariable = module.getGlobalVariable.bind(module) as any;
                getGlobalVariable(1);
            }).toThrowError(getGlobalVariableErrMsg);
        });
    });

    describe('Test llvm.Module.addModuleFlag', () => {
        const addModuleFlagErrMsg = 'Module.addModuleFlag needs to be called with (behavior: number, key: string, value: number)' + 
        '\n\t - limit: behavior ∈ [1, 7]';

        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            module.addModuleFlag(llvm.Module.ModFlagBehavior.Require, 'name', 1);
        });

        test('Test Without Enough Arguments', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag();
            }).toThrowError(addModuleFlagErrMsg);
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag(llvm.Module.ModFlagBehavior.Require);
            }).toThrowError(addModuleFlagErrMsg);
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag(llvm.Module.ModFlagBehavior.Require, 'name');
            }).toThrowError(addModuleFlagErrMsg);
        });

        test('Test With Arguments Not Matching The Expected Type', () => {
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag('param1', 'name', 1);
            }).toThrowError(addModuleFlagErrMsg);
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag(llvm.Module.ModFlagBehavior.Require, 2, 1);
            }).toThrowError(addModuleFlagErrMsg);
            expect(() => {
                const context = new llvm.LLVMContext();
                const module = new llvm.Module(FileName, context);
                const addModuleFlag = module.addModuleFlag.bind(module) as any;
                addModuleFlag(llvm.Module.ModFlagBehavior.Require, 'name', 'param3');
            }).toThrowError(addModuleFlagErrMsg);
        });
    });

    describe('Test llvm.Module.empty', () => {
        test('Test Empty Module', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            expect(module.empty()).toEqual(true);
        });

        test('Test Non-Empty Module', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            llvm.Function.Create(funcType, llvm.Function.LinkageTypes.ExternalLinkage, 'main', module);
            expect(module.empty()).toEqual(false);
        });
    });

    describe('Test llvm.Module.print', () => {
        test('Test Normally', () => {
            const context = new llvm.LLVMContext();
            const module = new llvm.Module(FileName, context);
            const funcType = llvm.FunctionType.get(llvm.Type.getVoidTy(context), false);
            const func = llvm.Function.Create(funcType, llvm.Function.LinkageTypes.ExternalLinkage, 'func', module);
            llvm.BasicBlock.Create(context, 'entry', func);
            expect(module.print()).toMatchSnapshot();
        });
    });
});
