import path from 'path';
import llvm from '..';

export default function testUnary(): void {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getVoidTy();
    const functionType = llvm.FunctionType.get(returnType, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'unary', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertPoint(entryBB);

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
    builder.CreateStore(llvm.ConstantFP.get(builder.getDoubleTy(), 11.1), floatAlloca);
    const floatValue = builder.CreateLoad(builder.getDoubleTy(), floatAlloca, 'float_value');
    const negFloatValue = builder.CreateFNeg(floatValue, 'neg_float_value');
    builder.CreateStore(negFloatValue, floatAlloca);

    builder.CreateRetVoid()

    console.log(module.print());

    if (llvm.verifyFunction(func)) {
        console.error(`${filename}: verifying the 'unary' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
}
