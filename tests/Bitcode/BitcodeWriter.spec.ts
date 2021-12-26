import fs from 'fs';
import path from 'path';
import llvm from '../..';

const outputBitcodeFileName = 'bitcode-writer-test.bc';

describe('Test BitcodeWriter', () => {
    beforeEach(() => {
        if (fs.existsSync(outputBitcodeFileName)) {
            fs.unlinkSync(outputBitcodeFileName);
        }
    });

    afterEach(() => {
        if (fs.existsSync(outputBitcodeFileName)) {
            fs.unlinkSync(outputBitcodeFileName);
        }
    });

    test('Test llvm.WriteBitcodeToFile', () => {
        const context = new llvm.LLVMContext();
        const module = new llvm.Module(path.basename(__filename), context);
        llvm.WriteBitcodeToFile(module, outputBitcodeFileName);
        expect(fs.existsSync(outputBitcodeFileName)).toBe(true);
    });
});
