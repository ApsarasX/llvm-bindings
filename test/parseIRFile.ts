import path from 'path';
import { LLVMContext, SMDiagnostic, parseIRFile, verifyModule } from '..';

export default function (): void {
    const filename = path.join(__dirname, 'bitcode/add.bc');
    const err = new SMDiagnostic();
    const context = new LLVMContext();
    const mod = parseIRFile(filename, err, context);
    if (!verifyModule(mod)) {
        mod.print();
    }
}
