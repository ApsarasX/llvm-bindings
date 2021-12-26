import llvm from '../..';

describe('Test llvm-config', () => {
    test('Test llvm.config Macros', () => {
        expect(llvm.config.LLVM_DEFAULT_TARGET_TRIPLE).toEqual(expect.any(String));
        expect(llvm.config.LLVM_HOST_TRIPLE).toEqual(expect.any(String));
        expect(llvm.config.LLVM_ON_UNIX).toEqual(expect.any(Number));
        expect(llvm.config.LLVM_VERSION_MAJOR).toEqual(expect.any(Number));
        expect(llvm.config.LLVM_VERSION_MINOR).toEqual(expect.any(Number));
        expect(llvm.config.LLVM_VERSION_PATCH).toEqual(expect.any(Number));
        expect(llvm.config.LLVM_VERSION_STRING).toEqual(expect.any(String));
    });
});
