import llvm from '../..';

describe('Test TargetRegistry', () => {
    let target: llvm.Target | null = null;

    beforeAll(() => {
        llvm.InitializeAllTargetInfos();
        llvm.InitializeAllTargets();
        llvm.InitializeAllTargetMCs();
        target = llvm.TargetRegistry.lookupTarget('x86_64');
    });

    test('Test llvm.TargetRegistry.lookupTarget', () => {
        expect(target).toBeInstanceOf(llvm.Target);
    });

    test('Test llvm.Target.getName', () => {
        expect(target).toBeInstanceOf(llvm.Target);
        if (target) {
            expect(target.getName()).toEqual('x86-64');
        }
    });

    test('Test llvm.Target.getShortDescription', () => {
        expect(target).toBeInstanceOf(llvm.Target);
        if (target) {
            expect(target.getShortDescription()).toEqual('64-bit X86: EM64T and AMD64');
        }
    });

    test('Test llvm.Target.createTargetMachine', () => {
        expect(target).toBeInstanceOf(llvm.Target);
        if (target) {
            const machine = target.createTargetMachine('x86_64-generic-generic', 'generic');
            expect(machine).toBeInstanceOf(llvm.TargetMachine);
        }
    });
});
