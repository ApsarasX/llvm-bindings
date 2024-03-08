import path from 'path';
import llvm from '..';

export default function testException() {
    const filename = path.basename(__filename);
    const context = new llvm.LLVMContext();
    const module = new llvm.Module(filename, context);
    const builder = new llvm.IRBuilder(context);

    const i8PtrType = builder.getInt8PtrTy();
    const voidType = builder.getVoidTy();

    const functionType = llvm.FunctionType.get(voidType, false);
    const mainFunc = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'exception', module);

    const allocExceptionFuncType = llvm.FunctionType.get(i8PtrType, [builder.getInt64Ty()], false);
    const allocExceptionFunc = module.getOrInsertFunction('__cxa_allocate_exception', allocExceptionFuncType);
    const throwFuncType = llvm.FunctionType.get(voidType, [i8PtrType, i8PtrType, i8PtrType], false);
    const throwFunc = module.getOrInsertFunction('__cxa_throw', throwFuncType);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', mainFunc);
    builder.SetInsertPoint(entryBB);

    const errMsgStr = builder.CreateGlobalString('error message');

    const tmp1 = builder.CreateCall(allocExceptionFunc, [builder.getInt64(8)]);
    const tmp2 = builder.CreateBitCast(tmp1, llvm.PointerType.getUnqual(builder.getInt8PtrTy()));
    builder.CreateStore(
        builder.CreateInBoundsGEP(
            errMsgStr.getValueType(),
            errMsgStr,
            [builder.getInt64(0), builder.getInt64(0)]
        ),
        tmp2
    );
    const tinfo = new llvm.GlobalVariable(
        module,
        builder.getInt8PtrTy(),
        true,
        llvm.Function.LinkageTypes.ExternalLinkage,
        null
    );
    const tmp3 = builder.CreateBitCast(tinfo, builder.getInt8PtrTy());
    builder.CreateCall(throwFunc, [tmp1, tmp3, llvm.ConstantPointerNull.get(builder.getInt8PtrTy())]);
    builder.CreateUnreachable();

    console.log(module.print());

    if (llvm.verifyFunction(mainFunc)) {
        console.error(`${filename}: verifying the 'exception' function failed`);
        process.exit(1);
    }
    if (llvm.verifyModule(module)) {
        console.error(`${filename}: verifying the module failed`);
        process.exit(1);
    }
}