import { BasicBlock, ConstantFP, verifyFunction, verifyModule } from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function (): void {
    const { context, module, builder } = getContextModuleBuilder('unary.cpp');
    const returnType = builder.getVoidTy();
    const func = createFunction('unary', returnType, [], module);
    const entryBB = BasicBlock.Create(context, 'entry', func);
    builder.SetInsertionPoint(entryBB);

    const boolAlloca = builder.CreateAlloca(builder.getInt1Ty(), null, 'bool_alloca');
    builder.CreateStore(builder.getFalse(), boolAlloca);
    const boolValue = builder.CreateLoad(builder.getInt1Ty(), boolAlloca, 'bool_value');
    const notBoolValue = builder.CreateNot(boolValue, 'not_bool_value');
    builder.CreateStore(notBoolValue, boolAlloca);

    const flagAlloca = builder.CreateAlloca(builder.getInt64Ty(), null, 'flag_alloca');
    builder.CreateStore(builder.getInt64(123), flagAlloca);
    const flagValue = builder.CreateLoad(builder.getInt64Ty(), flagAlloca, 'flag_value');
    const notFlagValue = builder.CreateNot(flagValue, 'not_flag_value');
    builder.CreateStore(notFlagValue, flagAlloca);

    const integerAlloca = builder.CreateAlloca(builder.getInt64Ty(), null, 'integer_alloca');
    builder.CreateStore(builder.getInt64(233), integerAlloca);
    const integerValue = builder.CreateLoad(builder.getInt64Ty(), integerAlloca, 'integer_value');
    const negIntegerValue = builder.CreateNeg(integerValue, 'neg_integer_value');
    builder.CreateStore(negIntegerValue, integerAlloca);

    const floatAlloca = builder.CreateAlloca(builder.getDoubleTy(), null, 'float_alloca');
    builder.CreateStore(ConstantFP.get(builder.getDoubleTy(), 11.1), floatAlloca);
    const floatValue = builder.CreateLoad(builder.getDoubleTy(), floatAlloca, 'float_value');
    const negFloatValue = builder.CreateFNeg(floatValue, 'neg_float_value');
    builder.CreateStore(negFloatValue, floatAlloca);

    builder.CreateRetVoid()

    if (!verifyFunction(func) && !verifyModule(module)) {
        module.print();
    }
}
