const path = require('path');
const {LLVMContext, SMDiagnostic, parseIRFile, verifyModule} = require('..');

module.exports = function () {
    const filename = path.join(__dirname, 'bitcode/add.bc');
    const err = new SMDiagnostic();
    const context = new LLVMContext();
    const mod = parseIRFile(filename, err, context);
    if (!verifyModule(mod)) {
        mod.print();
    }
}