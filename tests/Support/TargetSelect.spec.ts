import llvm from '../..';

describe('Test TargetSelect', () => {
    test('Test llvm.InitializeNativeTarget', () => {
        llvm.InitializeNativeTarget();
        llvm.InitializeNativeTargetAsmPrinter();
        llvm.InitializeNativeTargetAsmParser();
        llvm.InitializeNativeTargetDisassembler();
    });

    test('Test llvm.InitializeAllTargets', () => {
        llvm.InitializeAllTargetInfos();
        llvm.InitializeAllTargets();
        llvm.InitializeAllTargetMCs();
        llvm.InitializeAllAsmPrinters();
        llvm.InitializeAllAsmParsers();
        llvm.InitializeAllDisassemblers();
    });
});
