import { LLVMContext, Module, IRBuilder, FunctionType, Function, Type } from '..';

export function getContextModuleBuilder(moduleID: string) {
    const context = new LLVMContext();
    return {
        context,
        module: new Module(moduleID, context),
        builder: new IRBuilder(context)
    };
}

export function createFunction(name: string, returnType: Type, paramTypes: Type[], module: Module) {
    const functionType = paramTypes.length > 0
        ? FunctionType.get(returnType, paramTypes, false)
        : FunctionType.get(returnType, false);
    return Function.Create(functionType, Function.LinkageTypes.ExternalLinkage, name, module);
}
