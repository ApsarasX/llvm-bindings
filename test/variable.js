const {
    BasicBlock,
    verifyFunction,
    verifyModule
} = require('..');

const {getContextModuleBuilder, createFunction} = require('./util');

module.exports = function () {
    const {context, module, builder} = getContextModuleBuilder('variable.cpp');
    const func = createFunction('test', builder.getVoidTy(), null, module);
    const entryBB = BasicBlock.Create(context, "entry", func);
    builder.SetInsertionPoint(entryBB);
    const alloca = builder.CreateAlloca(builder.getInt32Ty(), null, "a");
    builder.CreateStore(builder.getInt32(11), alloca);

    const value = builder.CreateLoad(builder.getInt32Ty(), alloca);

    const cond = builder.CreateICmpSGT(value, builder.getInt32(10), "cond");

    builder.CreateSelect(cond, builder.getInt32(10), builder.getInt32(20));

    builder.CreateRetVoid();

    if (!verifyFunction(func) && !verifyModule(module)) {
        module.print();
    }
    return null;
}