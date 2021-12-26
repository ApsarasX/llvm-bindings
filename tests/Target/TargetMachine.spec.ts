import llvm from '../..';

describe('Test TargetMachine', () => {
    beforeAll(() => {
        llvm.InitializeAllTargetInfos();
        llvm.InitializeAllTargets();
        llvm.InitializeAllTargetMCs();
    });

    test('Test llvm.TargetMachine.createDataLayout', () => {
        const target = llvm.TargetRegistry.lookupTarget('x86_64');
        expect(target).not.toBeNull();
        if (target) {
            const machine = target.createTargetMachine('x86_64-unknown-unknown', 'generic');
            const dataLayout = machine.createDataLayout();
            expect(dataLayout).toBeInstanceOf(llvm.DataLayout);
        }
    });
});
