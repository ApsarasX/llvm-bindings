const {
    BasicBlock,
    verifyFunction,
    verifyModule
} = require('..');

const {getContextModuleBuilder, createFunction} = require('./util');

module.exports = function (toPrint = true) {
    const {context, module, builder} = getContextModuleBuilder('add.cpp');
    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const func = createFunction('add', returnType, paramTypes, module);
    const entryBB = BasicBlock.Create(context, "entry", func);
    builder.SetInsertionPoint(entryBB);
    const a = func.getArg(0);
    const b = func.getArg(1);
    const result = builder.CreateAdd(a, b);
    builder.CreateRet(result);
    if (!verifyFunction(func) && !verifyModule(module)) {
        if (toPrint) {
            module.print();
        }
        return module;
    }
    return null;
}