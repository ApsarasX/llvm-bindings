import path from 'path';
import { LLVMContext, SMDiagnostic, parseIRFile, verifyModule } from '..';

export default function (): void {
    const filename = path.join(__dirname, 'bitcode/add.bc');
    const err = new SMDiagnostic();
    const context = new LLVMContext();
    const module = parseIRFile(filename, err, context);
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}
