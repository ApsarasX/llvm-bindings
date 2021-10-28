import { strict as assert } from 'assert';
import { IntegerType, LLVMContext, PointerType, Type } from '..';

export default function () {
    const context = new LLVMContext();
    const type1 = Type.getInt32Ty(context);
    const type2 = IntegerType.get(context, 32);
    const type3 = Type.getInt8PtrTy(context);
    const type4 = PointerType.getUnqual(Type.getInt8Ty(context));
    const type5 = Type.getVoidTy(context);
    assert(Type.isSameType(type1, type2));
    assert(!Type.isSameType(type1, type3));
    assert(!Type.isSameType(type1, type4));
    assert(!Type.isSameType(type1, type5));
    assert(!Type.isSameType(type2, type3));
    assert(!Type.isSameType(type2, type4));
    assert(!Type.isSameType(type2, type5));
    assert(Type.isSameType(type3, type4));
    assert(!Type.isSameType(type3, type5));
    assert(!Type.isSameType(type4, type5));
}