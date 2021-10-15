import { verifyModule } from '..';
import { getContextModuleBuilder } from './util';

export default function (): void {
    const { module, builder } = getContextModuleBuilder('str.cpp');
    builder.CreateGlobalString('HelloWorld', 'str', 0, module);
    builder.CreateGlobalStringPtr('Bye Bye', 'str', 0, module);
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}
