const {LLVMContext, Module, IRBuilder, FunctionType, Function} = require('..');

function getContextModuleBuilder(moduleID) {
    const context = new LLVMContext();
    return {
        context,
        module: new Module(moduleID, context),
        builder: new IRBuilder(context)
    };
}

function createFunction(name, returnType, paramTypes, module) {
    const functionType = paramTypes ? FunctionType.get(returnType, paramTypes, false) : FunctionType.get(returnType, false);
    return Function.Create(functionType, Function.LinkageTypes.ExternalLinkage, name, module);
}

module.exports = {
    getContextModuleBuilder,
    createFunction
};