import path from 'path';
import llvm from '..';

export default function testStr(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    builder.CreateGlobalString('HelloWorld', 'str', 0, module);
    builder.CreateGlobalStringPtr('Bye Bye', 'str', 0, module);

    console.log(module.print());

    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
}
