import llvm from '..';

export default function testTarget(): void {
    // llvm.InitializeAllTargetInfos();
    // llvm.InitializeAllTargets();
    // llvm.InitializeAllTargetMCs();
    // llvm.InitializeAllAsmPrinters();
    // llvm.InitializeAllAsmParsers();
    // llvm.InitializeAllDisassemblers();
    llvm.InitializeNativeTarget();
    llvm.InitializeNativeTargetAsmPrinter();
    llvm.InitializeNativeTargetAsmParser();
    llvm.InitializeNativeTargetDisassembler();
}
