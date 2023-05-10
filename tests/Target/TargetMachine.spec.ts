import fs from 'fs';
import path from 'path';

import llvm from '../..';
import { createTestModule } from "./testModule";

const TARGET_TRIPLE = 'x86_64-unknown-unknown';
const TARGET_CPU = 'generic';
const TARGET_FEATURES = '';
const TARGET_GEN_OPT_LEVEL = llvm.CodeGenOpt.None
const TARGET_OPT_LEVEL = llvm.OptimizationLevel.O0;
const TARGET_RELOC_TYPE = llvm.Reloc.Static;
const TARGET_CODE_MODEL = llvm.CodeModel.Medium;
const TARGET_FORMAT = llvm.CodeGenFileType.Object;

describe('Test TargetMachine', () => {
    beforeAll(() => {
        llvm.InitializeAllAsmPrinters();
        llvm.InitializeAllAsmParsers();
        llvm.InitializeAllTargetInfos();
        llvm.InitializeAllTargets();
        llvm.InitializeAllTargetMCs();
    });

    test('Test llvm.TargetMachine.createDataLayout', () => {
        const target = llvm.TargetRegistry.lookupTarget('x86_64');
        expect(target).toBeInstanceOf(llvm.Target);
        if (target) {
            const machine = target.createTargetMachine(TARGET_TRIPLE, TARGET_CPU);
            const dataLayout = machine.createDataLayout();
            expect(dataLayout).toBeInstanceOf(llvm.DataLayout);
        }
    });

    test('Test llvm.TargetMachine.emitToFile', () => {
        const target = llvm.TargetRegistry.lookupTarget(TARGET_TRIPLE);

        if (!target) {
            return;
        }

        const targetMachine = target.createTargetMachine(
            TARGET_TRIPLE,
            TARGET_CPU,
            TARGET_FEATURES,
            TARGET_RELOC_TYPE,
            TARGET_CODE_MODEL,
            TARGET_GEN_OPT_LEVEL,
        );

        const mpm = new llvm.ModulePassManager(TARGET_OPT_LEVEL);
        const fpm = mpm.createFunctionPassManager(llvm.ThinOrFullLTOPhase.None);

        const module = createTestModule();
        const filePath = path.resolve(__dirname, 'target-machine.test.o');

        mpm.addVerifierPass();
        mpm.addFunctionPasses(fpm);
        mpm.run(module);

        targetMachine.emitToFile(module, filePath, TARGET_FORMAT);
        expect(fs.existsSync(filePath)).toBe(true);
        expect(fs.statSync(filePath)?.size).toBe(656);

        try {
            fs.unlinkSync(filePath);
        } finally {}
    });

    test('Test llvm.TargetMachine.emitToBuffer', () => {
        const target = llvm.TargetRegistry.lookupTarget(TARGET_TRIPLE);

        if (!target) {
            return;
        }

        const targetMachine = target.createTargetMachine(
            TARGET_TRIPLE,
            TARGET_CPU,
            TARGET_FEATURES,
            TARGET_RELOC_TYPE,
            TARGET_CODE_MODEL,
            TARGET_GEN_OPT_LEVEL,
        );

        const mpm = new llvm.ModulePassManager(TARGET_OPT_LEVEL);
        const fpm = mpm.createFunctionPassManager(llvm.ThinOrFullLTOPhase.None);

        const module = createTestModule();

        mpm.addVerifierPass();
        mpm.addFunctionPasses(fpm);
        mpm.run(module);

        const data = targetMachine.emitToBuffer(module, TARGET_FORMAT);
        expect(data.length).toBe(656);
    });
});
