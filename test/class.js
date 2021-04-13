const {
    BasicBlock,
    verifyFunction,
    verifyModule,
    StructType,
    PointerType
} = require('..');

const {getContextModuleBuilder, createFunction} = require('./util');

module.exports = function () {
    const {context, module, builder} = getContextModuleBuilder('class.cpp');
    const classStructType = StructType.create(context, [builder.getInt32Ty(), builder.getInt32Ty()], "Person");

    const returnType = builder.getVoidTy();
    const paramTypes = [PointerType.getUnqual(classStructType)];
    const func = createFunction('class_Person_constructor', returnType, paramTypes, module);

    const entryBB = BasicBlock.Create(context, "entry", func);
    builder.SetInsertionPoint(entryBB);

    const thisPtr = func.getArg(0);
    const propertyPtr = builder.CreateGEP(thisPtr, [
        builder.getInt32(0),
        builder.getInt32(1)
    ]);
    builder.CreateStore(builder.getInt32(111), propertyPtr);
    builder.CreateRetVoid();


    if (!verifyFunction(func) && !verifyModule(module)) {
        module.print();
    }
};