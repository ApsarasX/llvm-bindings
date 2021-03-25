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

        public static getInt1Ty(context: LLVMContext): IntegerType;

        public static getInt8Ty(context: LLVMContext): IntegerType;

        public static getInt16Ty(context: LLVMContext): IntegerType;

        public static getInt32Ty(context: LLVMContext): IntegerType;

        public static getInt64Ty(context: LLVMContext): IntegerType;

        public static getInt128Ty(context: LLVMContext): IntegerType;

        public static getIntNTy(context: LLVMContext, n: number): IntegerType;

        public static getInt1PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt8PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public static getInt32PtrTy(context: LLVMContext, addrSpace?: number): PointerType;

        public getTypeID(): number;

        public isVoidTy(): boolean;

        public isHalfTy(): boolean;

        public isBFloatTy(): boolean;

        public isFloatTy(): boolean;

        public isDoubleTy(): boolean;

        public isFloatingPointTy(): boolean;

        public isLabelTy(): boolean;

        public isIntegerTy(): boolean;

        public isFunctionTy(): boolean;

        public isStructTy(): boolean;

        public isArrayTy(): boolean;

        public isPointerTy(): boolean;

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

    class BasicBlock extends Value {
        public static Create(
            context: LLVMContext,
            name?: string,
            parent?: Function,
            insertBefore?: BasicBlock
        ): BasicBlock;

        protected constructor();
    }

    class User extends Value {
        public getOperand(index: number): Value;

        public setOperand(index: number, value: Value): void;

        public getNumOperands(): number;

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
        public static get(type: IntegerType, value: number, isSigned: boolean): ConstantInt;
        public static get(type: Type, value: APInt): Constant;
        public static get(type: Type, value: number, isSigned: boolean): Constant;

        public static getTrue(context: LLVMContext): ConstantInt;

        public static getFalse(context: LLVMContext): ConstantInt;

        protected constructor();
    }

    class ConstantFP extends Constant {
        public static get(type: Type, value: number): Constant;
        public static get(type: Type, value: APFloat): Constant;
        public static get(type: Type, value: string): Constant;
        public static get(context: LLVMContext, value: APFloat): ConstantFP;

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
        }

        protected constructor();
    }

    class GlobalObject extends GlobalValue {
        protected constructor();
    }

    class GlobalVariable extends GlobalObject {
        protected constructor();
    }

    class Function extends GlobalObject {
        public static Create(funcType: FunctionType, linkage: number, name?: string, module?: Module): Function;

        protected constructor();
    }

    class FunctionCallee {
        public getFunctionType(): FunctionType;

        public getCallee(): Value;

        protected constructor();
    }

    class DataLayout {
        protected constructor();
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
        public CreateAdd(lhs: Value, rhs: Value): Value;

        public CreateFAdd(lhs: Value, rhs: Value): Value;

        public CreateSub(lhs: Value, rhs: Value): Value;

        public CreateFSub(lhs: Value, rhs: Value): Value;

        public CreateMul(lhs: Value, rhs: Value): Value;

        public CreateFMul(lhs: Value, rhs: Value): Value;

        public CreateSDiv(lhs: Value, rhs: Value): Value;

        public CreateUDiv(lhs: Value, rhs: Value): Value;

        public CreateFDiv(lhs: Value, rhs: Value): Value;

        public CreateSRem(lhs: Value, rhs: Value): Value;

        public CreateURem(lhs: Value, rhs: Value): Value;

        public CreateFRem(lhs: Value, rhs: Value): Value;

        public CreateAnd(lhs: Value, rhs: Value): Value;

        public CreateOr(lhs: Value, rhs: Value): Value;

        public CreateXor(lhs: Value, rhs: Value): Value;

        public CreateShl(lhs: Value, rhs: Value): Value;

        public CreateAShr(lhs: Value, rhs: Value): Value;

        public CreateLShr(lhs: Value, rhs: Value): Value;

        public CreateICmpEQ(lhs: Value, rhs: Value): Value;

        public CreateICmpNE(lhs: Value, rhs: Value): Value;

        public CreateICmpSGE(lhs: Value, rhs: Value): Value;

        public CreateICmpSGT(lhs: Value, rhs: Value): Value;

        public CreateICmpSLE(lhs: Value, rhs: Value): Value;

        public CreateICmpSGT(lhs: Value, rhs: Value): Value;

        public CreateICmpUGE(lhs: Value, rhs: Value): Value;

        public CreateICmpUGT(lhs: Value, rhs: Value): Value;

        public CreateICmpULE(lhs: Value, rhs: Value): Value;

        public CreateICmpUGT(lhs: Value, rhs: Value): Value;

        public CreateFCmpOEQ(lhs: Value, rhs: Value): Value;

        public CreateFCmpONE(lhs: Value, rhs: Value): Value;

        public CreateFCmpOGE(lhs: Value, rhs: Value): Value;

        public CreateFCmpOGT(lhs: Value, rhs: Value): Value;

        public CreateFCmpOLE(lhs: Value, rhs: Value): Value;

        public CreateFCmpOGT(lhs: Value, rhs: Value): Value;

        public CreateFCmpUEQ(lhs: Value, rhs: Value): Value;

        public CreateFCmpUNE(lhs: Value, rhs: Value): Value;

        public CreateFCmpUGE(lhs: Value, rhs: Value): Value;

        public CreateFCmpUGT(lhs: Value, rhs: Value): Value;

        public CreateFCmpULE(lhs: Value, rhs: Value): Value;

        public CreateFCmpUGT(lhs: Value, rhs: Value): Value;

        public CreateAlloca(type: Type, arraySize?: Value, name?: string): Value;

        public CreateBr(destBB: BasicBlock): Value;

        public CreateCall(callee: Value, args: Value[], name?: string): Value;
        public CreateCall(funcType: FunctionType, callee: Value, args: Value[], name?: string): Value;

        public CreateCondBr(cond: Value, thenBB: BasicBlock, elseBB: BasicBlock): Value;

        public CreateLoad(type: Type, ptr: Value, name?: string): Value;

        public CreateRet(value: Value): Value;

        public CreateRetVoid(): Value;

        public CreateStore(value: Value, ptr: Value): Value;

        public SetInsertionPoint(basicBlock: BasicBlock): Value;
    }

    class Target {
        public createTargetMachine(targetTriple: string, cpu: string, features: string): void;

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

    function initializeAllTargetInfos(): void;

    function initializeAllTargets(): void;

    function initializeAllTargetMCs(): void;

    function initializeAllAsmParsers(): void;

    function initializeAllAsmPrinters(): void;
}


