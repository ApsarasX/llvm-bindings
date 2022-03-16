declare namespace llvm {
    class APInt {
        public constructor(numBits: number, value: number, isSigned?: boolean);
    }

    class APFloat {
        public constructor(value: number);
    }

    namespace LLVMConstants {
        const DEBUG_METADATA_VERSION: number;
    }

    namespace dwarf {
        namespace LLVMConstants {
            const DWARF_VERSION: number;
        }
        namespace TypeKind {
            const DW_ATE_address: number;
            const DW_ATE_boolean: number;
            const DW_ATE_complex_float: number;
            const DW_ATE_float: number;
            const DW_ATE_signed: number;
            const DW_ATE_signed_char: number;
            const DW_ATE_unsigned: number;
            const DW_ATE_unsigned_char: number;
            const DW_ATE_imaginary_float: number;
            const DW_ATE_packed_decimal: number;
            const DW_ATE_numeric_string: number;
            const DW_ATE_edited: number;
            const DW_ATE_signed_fixed: number;
            const DW_ATE_unsigned_fixed: number;
            const DW_ATE_decimal_float: number;
            const DW_ATE_UTF: number;
            const DW_ATE_UCS: number;
            const DW_ATE_ASCII: number;
            const DW_ATE_lo_user: number;
            const DW_ATE_hi_user: number;
        }
        namespace SourceLanguage {
            const DW_LANG_C89: number;
            const DW_LANG_C: number;
            const DW_LANG_Ada83: number;
            const DW_LANG_C_plus_plus: number;
            const DW_LANG_Cobol74: number;
            const DW_LANG_Cobol85: number;
            const DW_LANG_Fortran77: number;
            const DW_LANG_Fortran90: number;
            const DW_LANG_Pascal83: number;
            const DW_LANG_Modula2: number;
            const DW_LANG_Java: number;
            const DW_LANG_C99: number;
            const DW_LANG_Ada95: number;
            const DW_LANG_Fortran95: number;
            const DW_LANG_PLI: number;
            const DW_LANG_ObjC: number;
            const DW_LANG_ObjC_plus_plus: number;
            const DW_LANG_UPC: number;
            const DW_LANG_D: number;
            const DW_LANG_Python: number;
            const DW_LANG_OpenCL: number;
            const DW_LANG_Go: number;
            const DW_LANG_Modula3: number;
            const DW_LANG_Haskell: number;
            const DW_LANG_C_plus_plus_03: number;
            const DW_LANG_C_plus_plus_11: number;
            const DW_LANG_OCaml: number;
            const DW_LANG_Rust: number;
            const DW_LANG_C11: number;
            const DW_LANG_Swift: number;
            const DW_LANG_Julia: number;
            const DW_LANG_Dylan: number;
            const DW_LANG_C_plus_plus_14: number;
            const DW_LANG_Fortran03: number;
            const DW_LANG_Fortran08: number;
            const DW_LANG_RenderScript: number;
            const DW_LANG_BLISS: number;
            const DW_LANG_lo_user: number;
            const DW_LANG_hi_user: number;
        }
    }

    function WriteBitcodeToFile(module: Module, filename: string): void;

    namespace config {
        const LLVM_DEFAULT_TARGET_TRIPLE: string;
        const LLVM_HOST_TRIPLE: string;
        const LLVM_ON_UNIX: number;
        const LLVM_VERSION_MAJOR: number;
        const LLVM_VERSION_MINOR: number;
        const LLVM_VERSION_PATCH: number;
        const LLVM_VERSION_STRING: string;
    }

    class LLVMContext {
        public constructor();
    }

    class Module {
        public static readonly ModFlagBehavior: {
            Error: number;
            Warning: number;
            Require: number;
            Override: number;
            Append: number;
            AppendUnique: number;
            Max: number;
            ModFlagBehaviorFirstVal: number;
            ModFlagBehaviorLastVal: number;
        }

        public constructor(moduleID: string, context: LLVMContext);

        public getModuleIdentifier(): string;

        public getSourceFileName(): string;

        public getName(): string;

        public getDataLayoutStr(): string;

        public getDataLayout(): DataLayout;

        public getTargetTriple(): string;

        public setModuleIdentifier(moduleID: string): void;

        public setSourceFileName(sourceFileName: string): void;

        public setDataLayout(desc: string): void;
        public setDataLayout(dataLayout: DataLayout): void;

        public setTargetTriple(triple: string): void;

        public getFunction(name: string): Function | null;

        public getOrInsertFunction(name: string, funcType: FunctionType): FunctionCallee;

        public getGlobalVariable(name: string, allowInternal?: boolean): GlobalVariable | null;

        public addModuleFlag(behavior: number, key: string, value: number): void;

        public empty(): boolean;

        // customized
        public print(): string;
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

        public static getIntNTy(context: LLVMContext, numBits: number): IntegerType;

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

        public getPointerTo(addrSpace?: number): PointerType;

        public getPrimitiveSizeInBits(): number;

        public getPointerElementType(): Type;

        // extra
        public static isSameType(type1: Type, type2: Type): boolean;

        protected constructor();
    }

    class IntegerType extends Type {
        public static get(context: LLVMContext, numBits: number): IntegerType;

        // duplicated
        public isStructTy(): boolean;

        // duplicated
        public isIntegerTy(bitWidth?: number): boolean;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        protected constructor();
    }

    class FunctionType extends Type {
        public static get(returnType: Type, isVarArg: boolean): FunctionType;
        public static get(returnType: Type, paramTypes: Type[], isVarArg: boolean): FunctionType;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        protected constructor();
    }

    class FunctionCallee {
        public getFunctionType(): FunctionType;

        public getCallee(): Value;

        protected constructor();
    }

    class StructType extends Type {
        public static create(context: LLVMContext, name: string): StructType;
        public static create(context: LLVMContext, elementTypes: Type[], name: string): StructType;

        public static get(context: LLVMContext): StructType;
        public static get(context: LLVMContext, elementTypes: Type[]): StructType;

        public getTypeByName(name: string): StructType | null;

        public setBody(elementTypes: Type[]): void;

        // duplicated
        public getPointerTo(addrSpace?: number): PointerType;

        // duplicated
        public isStructTy(): boolean;

        // duplicated
        public isIntegerTy(bitWidth?: number): boolean;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        protected constructor();
    }

    class ArrayType extends Type {
        public static get(elemType: Type, numElements: number): ArrayType;

        public static isValidElementType(elemType: Type): boolean;

        public getNumElements(): number;

        public getElementType(): Type;

        // duplicated
        public isStructTy(): boolean;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        protected constructor();
    }

    class VectorType extends Type {
        // duplicated
        public isStructTy(): boolean;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        protected constructor();
    }

    class PointerType extends Type {
        public static get(elementType: Type, addrSpace: number): PointerType;

        public static getUnqual(elementType: Type): PointerType;

        public getElementType(): Type;

        // duplicated
        public isPointerTy(): boolean;

        // duplicated
        public isStructTy(): boolean;

        // duplicated
        public isIntegerTy(bitWidth?: number): boolean;

        // duplicated
        public isVoidTy(): boolean;

        // duplicated
        public getTypeID(): number;

        // duplicated
        public getPointerElementType(): Type;

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

        public user_empty(): boolean;

        protected constructor();
    }

    class Argument extends Value {
        public constructor(type: Type, name?: string, func?: Function, argNo?: number);

        public getParent(): Function;

        public getArgNo(): number;

        // duplicated
        public getType(): Type;

        // duplicated
        public setName(name: string): void;
    }

    class BasicBlock extends Value {
        public static Create(
            context: LLVMContext,
            name?: string,
            parent?: Function,
            insertBefore?: BasicBlock
        ): BasicBlock;

        public getParent(): Function | null;

        public getModule(): Module | null;

        public getTerminator(): Instruction | null;

        public getFirstNonPHI(): Instruction | null;

        public insertInto(parent: Function, insertBefore?: BasicBlock): void;

        public removeFromParent(): void;

        // customized
        public eraseFromParent(): void;

        // duplicated
        public use_empty(): boolean;

        // duplicated
        public getType(): Type;

        // extra
        public deleteSelf(): void;

        protected constructor();
    }

    class User extends Value {
        public getOperand(i: number): Value;

        public setOperand(i: number, value: Value): void;

        public getNumOperands(): number;

        // duplicated
        public getType(): Type;

        protected constructor();
    }

    class Constant extends User {
        public static getNullValue(type: Type): Constant;

        public static getAllOnesValue(type: Type): Constant;

        public isNullValue(): boolean;

        public isOneValue(): boolean;

        public isAllOnesValue(): boolean;

        // duplicated
        public getType(): Type;

        protected constructor();
    }

    class ConstantInt extends Constant {
        public static get(context: LLVMContext, value: APInt): ConstantInt;
        public static get(type: IntegerType, value: number, isSigned?: boolean): ConstantInt;
        public static get(type: Type, value: APInt): Constant;
        public static get(type: Type, value: number, isSigned?: boolean): Constant;

        public static getTrue(context: LLVMContext): ConstantInt;

        public static getFalse(context: LLVMContext): ConstantInt;

        // duplicated
        public getType(): IntegerType;

        protected constructor();
    }

    class ConstantFP extends Constant {
        public static get(type: Type, value: number): Constant;
        public static get(type: Type, value: APFloat): Constant;
        public static get(type: Type, value: string): Constant;
        public static get(context: LLVMContext, value: APFloat): ConstantFP;

        public static getNaN(type: Type): Constant

        // duplicated
        public getType(): Type;

        protected constructor();
    }

    class ConstantStruct extends Constant {
        public static get(type: StructType, values: Constant[]): Constant;

        // duplicated
        public getType(): StructType;

        protected constructor();
    }

    class ConstantPointerNull extends Constant {
        public static get(type: PointerType): ConstantPointerNull;

        public getType(): PointerType;

        protected constructor();
    }

    class ConstantExpr extends Constant {
        public static getBitCast(constant: Constant, type: Type): Constant;

        // duplicated
        public getType(): Type;

        protected constructor();
    }

    class UndefValue extends Constant {
        public static get(type: Type): UndefValue;

        // duplicated
        public getType(): Type;

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

        // duplicated
        public getType(): PointerType;

        public getValueType(): Type;

        protected constructor();
    }

    class GlobalObject extends GlobalValue {
        // duplicated
        public getType(): PointerType;

        // duplicated
        public getValueType(): Type;

        protected constructor();
    }

    class GlobalVariable extends GlobalObject {
        // customized
        public constructor(type: Type, isConstant: boolean, linkage: number, initializer?: Constant | null, name?: string);
        // customized
        public constructor(module: Module, type: Type, isConstant: boolean, linkage: number, initializer: Constant | null, name?: string);

        // duplicated
        public getType(): PointerType;

        // duplicated
        public getValueType(): Type;

        public removeFromParent(): void;

        public eraseFromParent(): void;

        public addDebugInfo(gv: DIGlobalVariableExpression): void;
    }

    class Function extends GlobalObject {
        public static Create(funcType: FunctionType, linkage: number, name?: string, module?: Module): Function;

        public arg_size(): number;

        public getArg(i: number): Argument;

        public getReturnType(): Type;

        // customized
        public addBasicBlock(basicBlock: BasicBlock): void;

        public getEntryBlock(): BasicBlock;

        // extra
        public getExitBlock(): BasicBlock;

        // customized
        public insertAfter(where: BasicBlock, basicBlock: BasicBlock): void;

        public deleteBody(): void;

        public removeFromParent(): void;

        public eraseFromParent(): void;

        // duplicated
        public use_empty(): boolean;

        // duplicated
        public user_empty(): boolean;

        // duplicated
        public getNumUses(): number;

        // duplicated
        public removeDeadConstantUsers(): void;

        public hasPersonalityFn(): boolean;

        public setPersonalityFn(fn: Constant): void;

        public setDoesNotThrow(): void;

        public setSubprogram(subprogram: DISubprogram): void;

        public getSubprogram(): DISubprogram;

        // duplicated
        public getType(): PointerType;

        protected constructor();
    }

    class Instruction extends User {
        public user_back(): Instruction | null;

        public getParent(): BasicBlock | null;

        public getModule(): Module | null;

        public getFunction(): Function | null;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class AllocaInst extends Instruction {
        public getAllocatedType(): Type;

        public getArraySize(): Value;

        // duplicated
        public getType(): PointerType;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class LoadInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class StoreInst extends Instruction {
        public getValueOperand(): Value;

        public getPointerOperand(): Value;

        public getPointerOperandType(): Type;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FenceInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class AtomicCmpXchgInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class AtomicRMWInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class GetElementPtrInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ICmpInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FCmpInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CallInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class SelectInst extends Instruction {
        public getCondition(): Value;

        public getTrueValue(): Value;

        public getFalseValue(): Value;

        public setCondition(value: Value): void;

        public setTrueValue(value: Value): void;

        public setFalseValue(value: Value): void;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class VAArgInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ExtractElementInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class InsertElementInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ShuffleVectorInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ExtractValueInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class InsertValueInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class PHINode extends Instruction {
        public addIncoming(value: Value, basicBlock: BasicBlock): void;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class LandingPadInst extends Instruction {
        public setCleanup(value: boolean): void;

        public addClause(clauseVal: Constant): void;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ReturnInst extends Instruction {
        public getReturnValue(): Value;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class BranchInst extends Instruction {
        public isUnconditional(): boolean;

        public isConditional(): boolean;

        public getCondition(): Value;

        public getNumSuccessors(): number;

        public getSuccessor(i: number): BasicBlock;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class SwitchInst extends Instruction {
        public addCase(onVal: ConstantInt, dest: BasicBlock): void;

        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class IndirectBrInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class InvokeInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CallBrInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ResumeInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CatchSwitchInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CleanupPadInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CatchPadInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CatchReturnInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class CleanupReturnInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class UnreachableInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class TruncInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class ZExtInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class SExtInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FPTruncInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FPExtInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class UIToFPInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class SIToFPInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FPToUIInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FPToSIInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class IntToPtrInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class PtrToIntInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class BitCastInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class AddrSpaceCastInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class FreezeInst extends Instruction {
        // duplicated
        public getType(): Type;

        // duplicated
        public setDebugLoc(location: DebugLoc): void;

        protected constructor();
    }

    class IRBuilder {
        public constructor(context: LLVMContext);
        public constructor(theBB: BasicBlock);
        public constructor(ip: Instruction);

        //===--------------------------------------------------------------------===//
        // Builder configuration methods
        //===--------------------------------------------------------------------===//

        public ClearInsertionPoint(): void;

        public GetInsertBlock(): BasicBlock | null;

        public SetInsertPoint(basicBlock: BasicBlock): void;
        public SetInsertPoint(inst: Instruction): void;

        public saveIP(): IRBuilder.InsertPoint;

        public saveAndClearIP(): IRBuilder.InsertPoint;

        public restoreIP(ip: IRBuilder.InsertPoint): void;

        public SetCurrentDebugLocation(location: DebugLoc): void;
        // extra
        public SetCurrentDebugLocation(location: DILocation): void;

        //===--------------------------------------------------------------------===//
        // Miscellaneous creation methods.
        //===--------------------------------------------------------------------===//

        public CreateGlobalString(str: string, name?: string, addrSpace?: number, module?: Module): GlobalVariable;

        public getInt1(value: boolean): ConstantInt;

        public getTrue(): ConstantInt;

        public getFalse(): ConstantInt;

        public getInt8(value: number): ConstantInt;

        public getInt16(value: number): ConstantInt;

        public getInt32(value: number): ConstantInt;

        public getInt64(value: number): ConstantInt;

        public getIntN(numBits: number, value: number): ConstantInt;

        public getInt(value: APInt): ConstantInt;

        //===--------------------------------------------------------------------===//
        // Type creation methods
        //===--------------------------------------------------------------------===//

        public getInt1Ty(): IntegerType;

        public getInt8Ty(): IntegerType;

        public getInt16Ty(): IntegerType;

        public getInt32Ty(): IntegerType;

        public getInt64Ty(): IntegerType;

        public getInt128Ty(): IntegerType;

        public getIntNTy(numBits: number): IntegerType;

        public getHalfTy(): Type;

        public getBFloatTy(): Type;

        public getFloatTy(): Type;

        public getDoubleTy(): Type;

        public getVoidTy(): Type;

        public getInt8PtrTy(addrSpace?: number): PointerType;

        public getIntPtrTy(dataLayout: DataLayout, addrSpace?: number): IntegerType;

        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Terminators
        //===--------------------------------------------------------------------===//

        public CreateRetVoid(): ReturnInst;

        public CreateRet(value: Value): ReturnInst;

        public CreateBr(destBB: BasicBlock): BranchInst;

        public CreateCondBr(cond: Value, thenBB: BasicBlock, elseBB: BasicBlock): BranchInst;

        public CreateSwitch(value: Value, dest: BasicBlock, numCases?: number): SwitchInst;

        public CreateIndirectBr(addr: Value, numDests?: number): IndirectBrInst;

        // customized
        public CreateInvoke(callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string): InvokeInst;
        public CreateInvoke(callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string): InvokeInst;
        public CreateInvoke(callee: FunctionCallee, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string): InvokeInst;
        public CreateInvoke(callee: FunctionCallee, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string): InvokeInst;
        public CreateInvoke(funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string): InvokeInst;
        public CreateInvoke(funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string): InvokeInst;

        public CreateResume(exn: Value): ResumeInst;

        public CreateUnreachable(): UnreachableInst;

        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Binary Operators
        //===--------------------------------------------------------------------===//

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

        public CreateNeg(value: Value, name?: string): Value;

        public CreateFNeg(value: Value, name?: string): Value;

        public CreateNot(value: Value, name?: string): Value;


        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Memory Instructions
        //===--------------------------------------------------------------------===//

        // customized
        public CreateAlloca(type: Type, arraySize?: Value | null, name?: string): AllocaInst;

        public CreateLoad(type: Type, ptr: Value, name?: string): LoadInst;

        public CreateStore(value: Value, ptr: Value): StoreInst;

        public CreateGEP(type: Type, ptr: Value, idxList: Value[], name?: string): Value;
        public CreateGEP(type: Type, ptr: Value, idx: Value, name?: string): Value;

        public CreateInBoundsGEP(type: Type, ptr: Value, idxList: Value[], name?: string): Value;
        public CreateInBoundsGEP(type: Type, ptr: Value, idx: Value, name?: string): Value;

        public CreateGlobalStringPtr(str: string, name?: string, addrSpace?: number, module?: Module): Constant;

        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Cast/Conversion Operators
        //===--------------------------------------------------------------------===//

        public CreateTrunc(value: Value, destType: Type, name?: string): Value;

        public CreateZExt(value: Value, destType: Type, name?: string): Value;

        public CreateSExt(value: Value, destType: Type, name?: string): Value;

        public CreateZExtOrTrunc(value: Value, destType: Type, name?: string): Value;

        public CreateSExtOrTrunc(value: Value, destType: Type, name?: string): Value;

        public CreateFPToUI(value: Value, destType: Type, name?: string): Value;

        public CreateFPToSI(value: Value, destType: Type, name?: string): Value;

        public CreateUIToFP(value: Value, destType: Type, name?: string): Value;

        public CreateSIToFP(value: Value, destType: Type, name?: string): Value;

        public CreateFPTrunc(value: Value, destType: Type, name?: string): Value;

        public CreateFPExt(value: Value, destType: Type, name?: string): Value;

        public CreatePtrToInt(value: Value, destType: Type, name?: string): Value;

        public CreateIntToPtr(value: Value, destType: Type, name?: string): Value;

        public CreateBitCast(value: Value, destType: Type, name?: string): Value;

        public CreateAddrSpaceCast(value: Value, destType: Type, name?: string): Value;

        public CreateZExtOrBitCast(value: Value, destType: Type, name?: string): Value;

        public CreateSExtOrBitCast(value: Value, destType: Type, name?: string): Value;

        public CreateTruncOrBitCast(value: Value, destType: Type, name?: string): Value;

        public CreatePointerCast(value: Value, destType: Type, name?: string): Value;

        public CreatePointerBitCastOrAddrSpaceCast(value: Value, destType: Type, name?: string): Value;

        public CreateIntCast(value: Value, destType: Type, isSigned: boolean, name?: string): Value;

        public CreateBitOrPointerCast(value: Value, destType: Type, name?: string): Value;

        public CreateFPCast(value: Value, destType: Type, name?: string): Value;

        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Compare Instructions
        //===--------------------------------------------------------------------===//

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


        //===--------------------------------------------------------------------===//
        // Instruction creation methods: Other Instructions
        //===--------------------------------------------------------------------===//

        public CreatePHI(type: Type, numReservedValues: number, name?: string): PHINode;

        // customized
        public CreateCall(callee: Function, name?: string): CallInst;
        public CreateCall(callee: Function, args: Value[], name?: string): CallInst;
        public CreateCall(callee: FunctionCallee, name?: string): CallInst;
        public CreateCall(callee: FunctionCallee, args: Value[], name?: string): CallInst;
        public CreateCall(funcType: FunctionType, callee: Value, name?: string): CallInst;
        public CreateCall(funcType: FunctionType, callee: Value, args: Value[], name?: string): CallInst;

        public CreateSelect(cond: Value, trueValue: Value, falseValue: Value, name?: string): Value;

        public CreateExtractValue(agg: Value, idxs: number[], name?: string): Value;

        public CreateInsertValue(agg: Value, value: Value, idxs: number[], name?: string): Value;

        public CreateLandingPad(type: Type, numClauses: number, name?: string): LandingPadInst;

        //===--------------------------------------------------------------------===//
        // Utility creation methods
        //===--------------------------------------------------------------------===//

        public CreateIsNull(value: Value, name?: string): Value;

        public CreateIsNotNull(value: Value, name?: string): Value;

        public CreatePtrDiff(lhs: Value, rhs: Value, name?: string): Value;
    }

    namespace IRBuilder {
        export class InsertPoint {
            protected constructor();
        }
    }

    class Metadata {
        protected constructor();
    }

    class MDNode extends Metadata {
        protected constructor();
    }

    class DebugLoc {
        public constructor();
    }

    class DITypeRefArray {
        protected constructor();
    }

    class DINode extends MDNode {
        public static readonly DIFlags: {
            FlagZero: number;
            FlagPrivate: number;
            FlagProtected: number;
            FlagPublic: number;
            FlagFwdDecl: number;
            FlagAppleBlock: number;
            FlagReservedBit4: number;
            FlagVirtual: number;
            FlagArtificial: number;
            FlagExplicit: number;
            FlagPrototyped: number;
            FlagObjcClassComplete: number;
            FlagObjectPointer: number;
            FlagVector: number;
            FlagStaticMember: number;
            FlagLValueReference: number;
            FlagRValueReference: number;
            FlagExportSymbols: number;
            FlagSingleInheritance: number;
            FlagMultipleInheritance: number;
            FlagVirtualInheritance: number;
            FlagIntroducedVirtual: number;
            FlagBitField: number;
            FlagNoReturn: number;
            FlagTypePassByValue: number;
            FlagTypePassByReference: number;
            FlagEnumClass: number;
            FlagThunk: number;
            FlagNonTrivial: number;
            FlagBigEndian: number;
            FlagLittleEndian: number;
            FlagAllCallsDescribed: number;
            FlagIndirectVirtualBase: number;
            FlagAccessibility: number;
            FlagPtrToMemberRep: number;
        }

        protected constructor();
    }

    class DIScope extends DINode {
        protected constructor();
    }

    class DIFile extends DIScope {
        protected constructor();
    }

    class DIType extends DIScope {
        protected constructor();
    }

    class DIBasicType extends DIType {
        protected constructor();
    }

    class DIDerivedType extends DIType {
        protected constructor();
    }

    class DICompositeType extends DIType {
        protected constructor();
    }

    class DISubroutineType extends DIType {
        protected constructor();
    }

    class DICompileUnit extends DIScope {
        public getFile(): DIFile;

        protected constructor();
    }

    class DILocalScope extends DIScope {
        protected constructor();
    }

    class DILocation extends MDNode {
        public static get(context: LLVMContext, line: number, column: number, metadata: Metadata): DILocation;
        public static get(context: LLVMContext, line: number, column: number, scope: DILocalScope): DILocation;

        protected constructor();
    }

    class DISubprogram extends DILocalScope {
        public static readonly DISPFlags: {
            SPFlagZero: number;
            SPFlagVirtual: number;
            SPFlagPureVirtual: number;
            SPFlagLocalToUnit: number;
            SPFlagDefinition: number;
            SPFlagOptimized: number;
            SPFlagPure: number;
            SPFlagElemental: number;
            SPFlagRecursive: number;
            SPFlagMainSubprogram: number;
            SPFlagDeleted: number;
            SPFlagObjCDirect: number;
            SPFlagNonvirtual: number;
            SPFlagVirtuality: number;
        }

        protected constructor();
    }

    class DILexicalBlock extends DILocalScope {
        protected constructor();
    }

    class DINamespace extends DIScope {
        protected constructor();
    }

    class DIVariable extends DINode {
        protected constructor();
    }

    class DIExpression extends MDNode {
        protected constructor();
    }

    class DIGlobalVariableExpression extends MDNode {
        protected constructor();
    }

    class DILocalVariable extends DIVariable {
        protected constructor();
    }

    class DIGlobalVariable extends DIVariable {
        protected constructor();
    }

    class DIBuilder {
        public constructor(module: Module);

        public createFile(filename: string, directory: string): DIFile;

        public createCompileUnit(lang: number, file: DIFile, producer: string, isOptimized: boolean, flags: string, rv: number): DICompileUnit;

        public createFunction(scope: DIScope, name: string, linkage: string, file: DIFile, line: number, type: DISubroutineType, scopeLine: number, flags: number, spFlags: number): DISubprogram;

        public createLexicalBlock(scope: DIScope, file: DIFile, line: number, column: number): DILexicalBlock;

        public createBasicType(name: string, sizeInBits: number, encoding: number): DIBasicType;

        public getOrCreateTypeArray(elements: (Metadata | null)[]): DITypeRefArray;

        public createSubroutineType(paramTypes: DITypeRefArray): DISubroutineType;

        public createExpression(): DIExpression;

        public createParameterVariable(scope: DIScope, name: string, argNo: number, file: DIFile, line: number, type: DIType, alwaysPreserve?: boolean): DILocalVariable;

        public createAutoVariable(scope: DIScope, name: string, file: DIFile, line: number, type: DIType | null, alwaysPreserve?: boolean): DILocalVariable;

        public createGlobalVariableExpression(context: DIScope, name: string, linkage: string, file: DIFile, line: number, type: DIType, IsLocalToUnit: boolean): DIGlobalVariableExpression;

        public insertDeclare(storage: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBB: BasicBlock): Instruction;
        public insertDeclare(storage: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBefore: Instruction): Instruction;

        public insertDbgValueIntrinsic(value: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBB: BasicBlock): Instruction;
        public insertDbgValueIntrinsic(value: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBefore: Instruction): Instruction;

        public finalizeSubprogram(subprogram: DISubprogram): void;

        public finalize(): void;
    }

    class DataLayout {
        public constructor(desc: string);

        public getStringRepresentation(): string;

        public getTypeAllocSize(type: Type): number;
    }

    function verifyFunction(func: Function): boolean;

    function verifyModule(module: Module): boolean;

    namespace Intrinsic {
        const abs: number;
        const addressofreturnaddress: number;
        const adjust_trampoline: number;
        const annotation: number;
        const assume: number;
        const bitreverse: number;
        const bswap: number;
        const call_preallocated_arg: number;
        const call_preallocated_setup: number;
        const call_preallocated_teardown: number;
        const canonicalize: number;
        const ceil: number;
        const clear_cache: number;
        const codeview_annotation: number;
        const convert_from_fp16: number;
        const convert_to_fp16: number;
        const copysign: number;
        const coro_alloc: number;
        const coro_alloca_alloc: number;
        const coro_alloca_free: number;
        const coro_alloca_get: number;
        const coro_async_context_alloc: number;
        const coro_async_context_dealloc: number;
        const coro_async_resume: number;
        const coro_begin: number;
        const coro_destroy: number;
        const coro_done: number;
        const coro_end: number;
        const coro_end_async: number;
        const coro_frame: number;
        const coro_free: number;
        const coro_id: number;
        const coro_id_async: number;
        const coro_id_retcon: number;
        const coro_id_retcon_once: number;
        const coro_noop: number;
        const coro_param: number;
        const coro_prepare_async: number;
        const coro_prepare_retcon: number;
        const coro_promise: number;
        const coro_resume: number;
        const coro_save: number;
        const coro_size: number;
        const coro_subfn_addr: number;
        const coro_suspend: number;
        const coro_suspend_async: number;
        const coro_suspend_retcon: number;
        const cos: number;
        const ctlz: number;
        const ctpop: number;
        const cttz: number;
        const dbg_addr: number;
        const dbg_declare: number;
        const dbg_label: number;
        const dbg_value: number;
        const debugtrap: number;
        const donothing: number;
        const eh_dwarf_cfa: number;
        const eh_exceptioncode: number;
        const eh_exceptionpointer: number;
        const eh_recoverfp: number;
        const eh_return_i32: number;
        const eh_return_i64: number;
        const eh_sjlj_callsite: number;
        const eh_sjlj_functioncontext: number;
        const eh_sjlj_longjmp: number;
        const eh_sjlj_lsda: number;
        const eh_sjlj_setjmp: number;
        const eh_sjlj_setup_dispatch: number;
        const eh_typeid_for: number;
        const eh_unwind_init: number;
        const exp: number;
        const exp2: number;
        const expect: number;
        const expect_with_probability: number;
        const fabs: number;
        const floor: number;
        const flt_rounds: number;
        const fma: number;
        const fmuladd: number;
        const fptosi_sat: number;
        const fptoui_sat: number;
        const frameaddress: number;
        const fshl: number;
        const fshr: number;
        const gcread: number;
        const gcroot: number;
        const gcwrite: number;
        const get_active_lane_mask: number;
        const get_dynamic_area_offset: number;
        const hwasan_check_memaccess: number;
        const hwasan_check_memaccess_shortgranules: number;
        const icall_branch_funnel: number;
        const init_trampoline: number;
        const instrprof_increment: number;
        const instrprof_increment_step: number;
        const instrprof_value_profile: number;
        const invariant_end: number;
        const invariant_start: number;
        const is_constant: number;
        const launder_invariant_group: number;
        const lifetime_end: number;
        const lifetime_start: number;
        const llrint: number;
        const llround: number;
        const load_relative: number;
        const localaddress: number;
        const localescape: number;
        const localrecover: number;
        const log: number;
        const log10: number;
        const log2: number;
        const loop_decrement: number;
        const loop_decrement_reg: number;
        const lrint: number;
        const lround: number;
        const masked_compressstore: number;
        const masked_expandload: number;
        const masked_gather: number;
        const masked_load: number;
        const masked_scatter: number;
        const masked_store: number;
        const matrix_column_major_load: number;
        const matrix_column_major_store: number;
        const matrix_multiply: number;
        const matrix_transpose: number;
        const maximum: number;
        const maxnum: number;
        const memcpy: number;
        const memcpy_element_unordered_atomic: number;
        const memcpy_inline: number;
        const memmove: number;
        const memmove_element_unordered_atomic: number;
        const memset: number;
        const memset_element_unordered_atomic: number;
        const minimum: number;
        const minnum: number;
        const nearbyint: number;
        const objc_arc_annotation_bottomup_bbend: number;
        const objc_arc_annotation_bottomup_bbstart: number;
        const objc_arc_annotation_topdown_bbend: number;
        const objc_arc_annotation_topdown_bbstart: number;
        const objc_autorelease: number;
        const objc_autoreleasePoolPop: number;
        const objc_autoreleasePoolPush: number;
        const objc_autoreleaseReturnValue: number;
        const objc_clang_arc_use: number;
        const objc_copyWeak: number;
        const objc_destroyWeak: number;
        const objc_initWeak: number;
        const objc_loadWeak: number;
        const objc_loadWeakRetained: number;
        const objc_moveWeak: number;
        const objc_release: number;
        const objc_retain: number;
        const objc_retain_autorelease: number;
        const objc_retainAutorelease: number;
        const objc_retainAutoreleaseReturnValue: number;
        const objc_retainAutoreleasedReturnValue: number;
        const objc_retainBlock: number;
        const objc_retainedObject: number;
        const objc_storeStrong: number;
        const objc_storeWeak: number;
        const objc_sync_enter: number;
        const objc_sync_exit: number;
        const objc_unretainedObject: number;
        const objc_unretainedPointer: number;
        const objc_unsafeClaimAutoreleasedReturnValue: number;
        const objectsize: number;
        const pcmarker: number;
        const pow: number;
        const powi: number;
        const prefetch: number;
        const preserve_array_access_index: number;
        const preserve_struct_access_index: number;
        const preserve_union_access_index: number;
        const pseudoprobe: number;
        const ptr_annotation: number;
        const ptrmask: number;
        const read_register: number;
        const read_volatile_register: number;
        const readcyclecounter: number;
        const returnaddress: number;
        const rint: number;
        const round: number;
        const roundeven: number;
        const sadd_sat: number;
        const sadd_with_overflow: number;
        const sdiv_fix: number;
        const sdiv_fix_sat: number;
        const set_loop_iterations: number;
        const sideeffect: number;
        const sin: number;
        const smax: number;
        const smin: number;
        const smul_fix: number;
        const smul_fix_sat: number;
        const smul_with_overflow: number;
        const sponentry: number;
        const sqrt: number;
        const ssa_copy: number;
        const sshl_sat: number;
        const ssub_sat: number;
        const ssub_with_overflow: number;
        const stackguard: number;
        const stackprotector: number;
        const stackrestore: number;
        const stacksave: number;
        const start_loop_iterations: number;
        const strip_invariant_group: number;
        const test_set_loop_iterations: number;
        const thread_pointer: number;
        const trap: number;
        const trunc: number;
        const type_checked_load: number;
        const type_test: number;
        const uadd_sat: number;
        const uadd_with_overflow: number;
        const ubsantrap: number;
        const udiv_fix: number;
        const udiv_fix_sat: number;
        const umax: number;
        const umin: number;
        const umul_fix: number;
        const umul_fix_sat: number;
        const umul_with_overflow: number;
        const ushl_sat: number;
        const usub_sat: number;
        const usub_with_overflow: number;
        const vacopy: number;
        const vaend: number;
        const vastart: number;
        const var_annotation: number;
        const vector_reduce_add: number;
        const vector_reduce_and: number;
        const vector_reduce_fadd: number;
        const vector_reduce_fmax: number;
        const vector_reduce_fmin: number;
        const vector_reduce_fmul: number;
        const vector_reduce_mul: number;
        const vector_reduce_or: number;
        const vector_reduce_smax: number;
        const vector_reduce_smin: number;
        const vector_reduce_umax: number;
        const vector_reduce_umin: number;
        const vector_reduce_xor: number;
        const vp_add: number;
        const vp_and: number;
        const vp_ashr: number;
        const vp_lshr: number;
        const vp_mul: number;
        const vp_or: number;
        const vp_sdiv: number;
        const vp_shl: number;
        const vp_srem: number;
        const vp_sub: number;
        const vp_udiv: number;
        const vp_urem: number;
        const vp_xor: number;
        const vscale: number;
        const write_register: number;
        const xray_customevent: number;
        const xray_typedevent: number;

        function getDeclaration(module: Module, id: number, types?: Type[]): Function;
    }

    function parseIRFile(filename: string, err: SMDiagnostic, context: LLVMContext): Module;

    class Linker {
        public constructor(module: Module);

        public linkInModule(srcModule: Module): boolean;

        public static linkModules(destModule: Module, srcModule: Module): boolean;
    }

    class SMDiagnostic {
        public constructor();
    }

    class Target {
        public createTargetMachine(targetTriple: string, cpu: string, features?: string): TargetMachine;

        public getName(): string;

        public getShortDescription(): string;

        protected constructor();
    }

    class TargetRegistry {
        static lookupTarget(target: string): Target | null;

        protected constructor();
    }

    class TargetMachine {
        public createDataLayout(): DataLayout;

        protected constructor();
    }

    function InitializeAllTargetInfos(): void;

    function InitializeAllTargets(): void;

    function InitializeAllTargetMCs(): void;

    function InitializeAllAsmPrinters(): void;

    function InitializeAllAsmParsers(): void;

    function InitializeAllDisassemblers(): void;

    function InitializeNativeTarget(): boolean;

    function InitializeNativeTargetAsmPrinter(): boolean;

    function InitializeNativeTargetAsmParser(): boolean;

    function InitializeNativeTargetDisassembler(): boolean;
}

export = llvm;

export as namespace llvm;
