const {
    verifyModule
} = require('..');

const {getContextModuleBuilder} = require('./util');

module.exports = function () {
    const {module, builder} = getContextModuleBuilder('str.cpp');
    builder.CreateGlobalString("HelloWorld", "str", 0, module);
    builder.CreateGlobalStringPtr("Bye Bye", "str", 0, module);
    if (!verifyModule(module)) {
        module.print();
    }
}