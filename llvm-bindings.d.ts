declare namespace llvm {
    class APInt {
        public constructor(numBits: number, value: number, isSigned?: boolean);
    }

    class APFloat {
        public constructor(value: number);
    }

    class LLVMContext {
        public constructor();
    }

    class Type {
        public static readonly TypeID: {
            HalfTyID: number;
            BFloatTyID: number;
            FloatTyID: number;
            DoubleTyID: number;
            X86_FP80TyID: number;
            FP128TyID: number;
            PPC_FP128TyID: number;
            VoidTyID: number;
            LabelTyID: number;
            MetadataTyID: number;
            X86_MMXTyID: number;
            TokenTyID: number;
            IntegerTyID: number;
            FunctionTyID: number;
            PointerTyID: number;
            StructTyID: number;
            ArrayTyID: number;
            FixedVectorTyID: number;
            ScalableVectorTyID: number;
        };

        public static getVoidTy(context: LLVMContext): Type;

        public static getLabelTy(context: LLVMContext): Type;

        public static getHalfTy(context: LLVMContext): Type;

        public static getBFloatTy(context: LLVMContext): Type;

        public static getFloatTy(context: LLVMContext): Type;

        public static getDoubleTy(context: LLVMContext): Type;

        public static getMetadataTy(context: LLVMContext): Type;

        public static getX86_FP80Ty(context: LLVMContext): Type;

        public static getFP128Ty(context: LLVMContext): Type;

        public static getPPC_FP128Ty(context: LLVMContext): Type;

        public static getX86_MMXTy(context: LLVMContext): Type;

        public static getTokenTy(context: LLVMContext): Type;

        public static getIntNTy(context: LLVMContext, n: number): IntegerType;

        public static getInt1Ty(context: LLVMContext): IntegerType;

        public static getInt8Ty(context: LLVMContext): IntegerType;

        public static getInt16Ty(context: LLVMContext): IntegerType;

        public static getInt32Ty(context: LLVMContext): IntegerType;

        public static getInt64Ty(context: LLVMContext): IntegerType;

        public static getInt128Ty(context: LLVMContext): IntegerType;

        public static getHalfPtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getBFloatPtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getFloatPtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getDoublePtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getX86_FP80PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getFP128PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getPPC_FP128PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getX86_MMXPtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt1PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt8PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt16PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt32PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt64PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public getTypeID(): number;

        public isVoidTy(): boolean;

        public isHalfTy(): boolean;

        public isBFloatTy(): boolean;

        public isFloatTy(): boolean;

        public isDoubleTy(): boolean;

        public isX86_FP80Ty(): boolean;

        public isFP128Ty(): boolean;

        public isPPC_FP128Ty(): boolean;

        public isFloatingPointTy(): boolean;

        public isX86_MMXTy(): boolean;

        public isLabelTy(): boolean;

        public isMetadataTy(): boolean;

        public isTokenTy(): boolean;

        public isIntegerTy(bitWidth?: number): boolean;

        public isFunctionTy(): boolean;

        public isStructTy(): boolean;

        public isArrayTy(): boolean;

        public isPointerTy(): boolean;

        public isVectorTy(): boolean;

        public isEmptyTy(): boolean;

        public isFirstClassType(): boolean;

        public isSingleValueType(): boolean;

        public isAggregateType(): boolean;

        public getPointerTo(addrSpace?: number): Type;

        public getPrimitiveSizeInBits(): number;

        protected constructor();
    }

    class IntegerType extends Type {
        public static get(context: LLVMContext, numBits: number): IntegerType;

        protected constructor();
    }

    class PointerType extends Type {
        public static get(elementType: Type, addrSpace: number): PointerType;

        public getElementType(): Type;

        protected constructor();
    }

    class FunctionType extends Type {
        public static get(returnType: Type, isVarArg: boolean): FunctionType;
        public static get(returnType: Type, paramTypes: Type[], isVarArg: boolean): FunctionType;

        protected constructor();
    }

    class StructType extends Type {
        protected constructor();
    }

    class ArrayType extends Type {
        public static get(elemType: Type, numElements: number): ArrayType;

        public static isValidElementType(elemType: Type): boolean;

        public getNumElements(): number;

        public getElementType(): Type;

        protected constructor();
    }

    class Value {
        public static MaxAlignmentExponent: number;
        public static MaximumAlignment: number;

        public getType(): Type;

        public hasName(): boolean;

        public getName(): string;

        public setName(name: string): void;

        public deleteValue(): void;

        public replaceAllUsesWith(newValue: Value): void;

        public use_empty(): boolean;

        protected constructor();
    }

    class Argument extends Value {
        public constructor(type: Type, name?: string, func?: Function, argNo?: number);

        public getParent(): Function;

        public getArgNo(): number;
    }

    class BasicBlock extends Value {
        public static Create(
            context: LLVMContext,
            name?: string,
            parent?: Function,
            insertBefore?: BasicBlock
        ): BasicBlock;

        public getParent(): Function;

        public getModule(): Module;

        public getTerminator(): Instruction;

        public getFirstNonPHI(): Instruction;

        protected constructor();
    }

    class User extends Value {
        public getOperand(i: number): Value;

        public setOperand(i: number, value: Value): void;

        public getNumOperands(): number;

        protected constructor();
    }

    class Instruction extends User {
        public user_back(): Instruction;

        public getParent(): BasicBlock;

        public getModule(): Module;

        public getFunction(): Function;

        protected constructor();
    }

    class AllocaInst extends Instruction {
        public getAllocatedType(): Type;

        public getArraySize(): Value;

        protected constructor();
    }

    class BranchInst extends Instruction {
        public isUnconditional(): boolean;

        public isConditional(): boolean;

        public getCondition(): Value;

        public getNumSuccessors(): number;

        public getSuccessor(i: number): BasicBlock;

        protected constructor();
    }

    class CallInst extends Instruction {
        protected constructor();
    }

    class LoadInst extends Instruction {
        protected constructor();
    }

    class ReturnInst extends Instruction {
        public getReturnValue(): Value;

        protected constructor();
    }

    class StoreInst extends Instruction {
        public getValueOperand(): Value;

        public getPointerOperand(): Value;

        public getPointerOperandType(): Type;

        protected constructor();
    }

    class Constant extends User {
        public static getNullValue(type: Type): Constant;

        public static getAllOnesValue(type: Type): Constant;

        public isNullValue(): boolean;

        public isOneValue(): boolean;

        public isAllOnesValue(): boolean;

        protected constructor();
    }

    class ConstantInt extends Constant {
        public static get(context: LLVMContext, value: APInt): ConstantInt;
        public static get(type: IntegerType, value: number, isSigned?: boolean): ConstantInt;
        public static get(type: Type, value: APInt): Constant;
        public static get(type: Type, value: number, isSigned?: boolean): Constant;

        public static getTrue(context: LLVMContext): ConstantInt;

        public static getFalse(context: LLVMContext): ConstantInt;

        protected constructor();
    }

    class ConstantFP extends Constant {
        public static get(type: Type, value: number): Constant;
        public static get(type: Type, value: APFloat): Constant;
        public static get(type: Type, value: string): Constant;
        public static get(context: LLVMContext, value: APFloat): ConstantFP;

        public static getNaN(type: Type): Constant

        protected constructor();
    }

    class ConstantPointerNull extends Constant {
        public static get(type: PointerType): ConstantPointerNull;

        public getType(): PointerType;

        protected constructor();
    }

    class GlobalValue extends Constant {
        public static readonly LinkageTypes: {
            ExternalLinkage: number;
            AvailableExternallyLinkage: number;
            LinkOnceAnyLinkage: number;
            LinkOnceODRLinkage: number;
            WeakAnyLinkage: number;
            WeakODRLinkage: number;
            AppendingLinkage: number;
            InternalLinkage: number;
            PrivateLinkage: number;
            ExternalWeakLinkage: number;
            CommonLinkage: number;
        };
        public static readonly VisibilityTypes: {
            DefaultVisibility: number;
            HiddenVisibility: number;
            ProtectedVisibility: number;
        }

        protected constructor();
    }

    class GlobalObject extends GlobalValue {
        protected constructor();
    }

    class GlobalVariable extends GlobalObject {
        public constructor(type: Type, isConstant: boolean, linkage: number, initializer?: Constant, name?: string);
        public constructor(module: Module, type: Type, isConstant: boolean, linkage: number, initializer: Constant, name?: string);
    }

    class Function extends GlobalObject {
        public static Create(funcType: FunctionType, linkage: number, name?: string, module?: Module): Function;

        public arg_size(): number;

        public getArg(i: number): Argument;

        protected constructor();
    }

    class DataLayout {
        public constructor(desc: string);
    }

    class Module {
        public constructor(moduleID: string, context: LLVMContext);

        public empty(): boolean;

        public getFunction(name: string): Function | null;

        public getGlobalVariable(name: string, allowInternal?: boolean): GlobalVariable | null;

        public getTypeByName(name: string): StructType | null;

        public getName(): string;

        public getDataLayout(): DataLayout;

        public setDataLayout(desc: string): void;
        public setDataLayout(dataLayout: DataLayout): void;

        public getModuleIdentifier(): string;

        public setModuleIdentifier(moduleID: string): void;

        public getSourceFileName(): string;

        public setSourceFileName(sourceFileName: string): void;

        public getTargetTriple(): string;

        public setTargetTriple(triple: string): void;

        public print(): void;
    }

    class IRBuilder {
        public constructor(context: LLVMContext);

        public CreateAdd(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFAdd(lhs: Value, rhs: Value, name?: string): Value;

        public CreateSub(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFSub(lhs: Value, rhs: Value, name?: string): Value;

        public CreateMul(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFMul(lhs: Value, rhs: Value, name?: string): Value;

        public CreateSDiv(lhs: Value, rhs: Value, name?: string): Value;

        public CreateUDiv(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFDiv(lhs: Value, rhs: Value, name?: string): Value;

        public CreateSRem(lhs: Value, rhs: Value, name?: string): Value;

        public CreateURem(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFRem(lhs: Value, rhs: Value, name?: string): Value;

        public CreateAnd(lhs: Value, rhs: Value, name?: string): Value;

        public CreateOr(lhs: Value, rhs: Value, name?: string): Value;

        public CreateXor(lhs: Value, rhs: Value, name?: string): Value;

        public CreateShl(lhs: Value, rhs: Value, name?: string): Value;

        public CreateAShr(lhs: Value, rhs: Value, name?: string): Value;

        public CreateLShr(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpEQ(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpNE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpSGE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpSGT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpSLE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpSLT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpUGE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpUGT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpULE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateICmpULT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpOEQ(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpONE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpOGE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpOGT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpOLE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpOLT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpUEQ(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpUNE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpUGE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpUGT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpULE(lhs: Value, rhs: Value, name?: string): Value;

        public CreateFCmpULT(lhs: Value, rhs: Value, name?: string): Value;

        public CreateAlloca(type: Type, arraySize?: Value, name?: string): Value;

        public CreateBr(destBB: BasicBlock): Value;

        public CreateCall(callee: Function, args: Value[], name?: string): Value;
        public CreateCall(funcType: FunctionType, callee: Value, args: Value[], name?: string): Value;

        public CreateCondBr(cond: Value, thenBB: BasicBlock, elseBB: BasicBlock): Value;

        public CreateLoad(type: Type, ptr: Value, name?: string): Value;

        public CreateRet(value: Value): Value;

        public CreateRetVoid(): Value;

        public CreateStore(value: Value, ptr: Value): Value;

        public SetInsertionPoint(basicBlock: BasicBlock): Value;

        public getInt1(value: boolean): ConstantInt;

        public getTrue(): ConstantInt;

        public getFalse(): ConstantInt;

        public getInt8(value: number): ConstantInt;

        public getInt16(value: number): ConstantInt;

        public getInt32(value: number): ConstantInt;

        public getInt64(value: number): ConstantInt;

        public getIntN(n: number, value: number): ConstantInt;

        public getInt(value: APInt): ConstantInt;

        public getInt1Ty(): IntegerType;

        public getInt8Ty(): IntegerType;

        public getInt16Ty(): IntegerType;

        public getInt32Ty(): IntegerType;

        public getInt64Ty(): IntegerType;

        public getInt128Ty(): IntegerType;

        public getIntNTy(n: number): IntegerType;

        public getHalfTy(): Type;

        public getBFloatTy(): Type;

        public getFloatTy(): Type;

        public getDoubleTy(): Type;

        public getVoidTy(): Type;

        public getInt8PtrTy(addrSpace?: number): PointerType;

        public getIntPtrTy(dataLayout: DataLayout, addrSpace?: number): IntegerType;
    }

    function verifyFunction(func: Function): boolean;

    function verifyModule(module: Module): boolean;

    function WriteBitcodeToFile(module: Module, filename: string): void;

    function parseIRFile(filename: string, err: SMDiagnostic, context: LLVMContext): Module;

    class Target {
        public createTargetMachine(targetTriple: string, cpu: string, features?: string): void;

        public getName(): string;

        public getShortDescription(): string;

        protected constructor();
    }

    class TargetRegistry {
        static lookupTarget(target: string): Target;

        protected constructor();
    }

    class TargetMachine {
        protected constructor();
    }

    class SMDiagnostic {
        public constructor();
    }

    function initializeAllTargetInfos(): void;

    function initializeAllTargets(): void;

    function initializeAllTargetMCs(): void;

    function initializeAllAsmParsers(): void;

    function initializeAllAsmPrinters(): void;
}

export = llvm;

export as namespace llvm;