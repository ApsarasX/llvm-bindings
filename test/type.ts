import { strict as assert } from 'assert';
import llvm from '..';

export default function testType() {
    const context = new llvm.LLVMContext();
    const type1 = llvm.Type.getInt32Ty(context);
    const type2 = llvm.IntegerType.get(context, 32);
    const type3 = llvm.Type.getInt8PtrTy(context);
    const type4 = llvm.PointerType.getUnqual(llvm.Type.getInt8Ty(context));
    const type5 = llvm.Type.getVoidTy(context);
    assert(llvm.Type.isSameType(type1, type2));
    assert(!llvm.Type.isSameType(type1, type3));
    assert(!llvm.Type.isSameType(type1, type4));
    assert(!llvm.Type.isSameType(type1, type5));
    assert(!llvm.Type.isSameType(type2, type3));
    assert(!llvm.Type.isSameType(type2, type4));
    assert(!llvm.Type.isSameType(type2, type5));
    assert(llvm.Type.isSameType(type3, type4));
    assert(!llvm.Type.isSameType(type3, type5));
    assert(!llvm.Type.isSameType(type4, type5));
}