import {
    BasicBlock,
    ConstantPointerNull,
    Function,
    FunctionType,
    GlobalVariable,
    PointerType,
    verifyFunction,
    verifyModule
} from '..';
import { getContextModuleBuilder, createFunction } from './util';

export default function () {
    const { context, module, builder } = getContextModuleBuilder('exception.cpp');
    const i8PtrType = builder.getInt8PtrTy();
    const voidType = builder.getVoidTy();
    const mainFunc = createFunction('main', voidType, [], module);
    const allocExceptionFuncType = FunctionType.get(i8PtrType, [builder.getInt64Ty()], false);
    const allocExceptionFunc = module.getOrInsertFunction('__cxa_allocate_exception', allocExceptionFuncType);
    const throwFuncType = FunctionType.get(voidType, [i8PtrType, i8PtrType, i8PtrType], false);
    const throwFunc = module.getOrInsertFunction('__cxa_throw', throwFuncType);

    const entryBB = BasicBlock.Create(context, 'entry', mainFunc);
    builder.SetInsertPoint(entryBB);

    const errMsgStr = builder.CreateGlobalString('error message');

    const tmp1 = builder.CreateCall(allocExceptionFunc, [builder.getInt64(8)]);
    const tmp2 = builder.CreateBitCast(tmp1, PointerType.getUnqual(builder.getInt8PtrTy()));
    builder.CreateStore(
        builder.CreateInBoundsGEP(
            errMsgStr.getType().getPointerElementType(),
            errMsgStr,
            [builder.getInt64(0), builder.getInt64(0)]
        ),
        tmp2
    );
    const tinfo = new GlobalVariable(
        module,
        builder.getInt8PtrTy(),
        true,
        Function.LinkageTypes.ExternalLinkage,
        null
    );
    const tmp3 = builder.CreateBitCast(tinfo, builder.getInt8PtrTy());
    builder.CreateCall(throwFunc, [tmp1, tmp3, ConstantPointerNull.get(builder.getInt8PtrTy())]);
    builder.CreateUnreachable();

    if (verifyFunction(mainFunc)) {
        console.error('Verifying function failed');
        return;
    }
    if (verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}