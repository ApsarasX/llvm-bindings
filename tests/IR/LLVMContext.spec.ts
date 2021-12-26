import llvm from '../..';

describe('Test LLVMContext', () => {
    test('Test llvm.LLVMContext.constructor', () => {
        const context = new llvm.LLVMContext();
        expect(context).toBeInstanceOf(llvm.LLVMContext);
    });
});
