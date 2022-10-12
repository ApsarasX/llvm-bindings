#pragma once

namespace ErrMsg {
    namespace Class {
        namespace APInt {
            constexpr const char *constructor = "APInt.constructor needs to be called with new (numBits: number, value: number, isSigned?: boolean)";
        }
        namespace APFloat {
            constexpr const char *constructor = "APFloat.constructor needs to be called with new (value: number)";
        }
        namespace LLVMContext {
            constexpr const char *constructor = "LLVMContext.constructor needs to be called with new ()";
        }
        namespace Module {
            constexpr const char *constructor = "Module.constructor needs to be called with"
                                                "\n\t - new (external: Napi::External<llvm::Module>)"
                                                "\n\t - new (moduleID: string, context: LLVMContext)";
            constexpr const char *setModuleIdentifier = "Module.setModuleIdentifier needs to be called with: (moduleID: string)";
            constexpr const char *setSourceFileName = "Module.setSourceFileName needs to be called with: (sourceFileName: string)";
            constexpr const char *setDataLayout = "Module.setDataLayout needs to be called with:"
                                                  "\n\t - (desc: string)"
                                                  "\n\t - (dataLayout: DataLayout)";
            constexpr const char *setTargetTriple = "Module.setTargetTriple needs to be called with: (targetTriple: string)";
            constexpr const char *getFunction = "Module.getFunction needs to be called with: (name: string)";
            constexpr const char *getOrInsertFunction = "Module.getOrInsertFunction needs to be called with: (name: string, fnType: FunctionType)";
            constexpr const char *getGlobalVariable = "Module.getGlobalVariable needs to be called with: (name: string, allowInternal?: boolean)";
            constexpr const char *addModuleFlag = "Module.addModuleFlag needs to be called with (behavior: number, key: string, value: number)"
                                                  "\n\t - limit: behavior should belong to [1, 7]";
        }
        namespace Type {
            constexpr const char *constructor = "Type.constructor needs to be called with new (external: Napi::External<llvm::Type>)";
            constexpr const char *getPointerTo = "Type.getPointer needs to called with: (addrSpace?: number)";
            constexpr const char *getIntNTy = "Type.getIntNTy needs to be called with: (context: LLVMContext, numBits: number)";
            constexpr const char *isIntegerTy = "Type.isIntegerTy needs to be called with: (bitWidth?: number)";
            constexpr const char *getTypeFactory = "Type.[getType] needs to be called with (context: LLVMContext)";
            constexpr const char *getIntTypeFactory = "Type.[getIntType] needs to be called with (context: LLVMContext)";
            constexpr const char *getPointerTypeFactory = "Type.[getPointerType] needs to be called with (context: LLVMContext, addrSpace?: number)";
            constexpr const char *isSameType = "Type.isSameType needs to be called with (type1: Type, type2: Type)";
        }
        namespace IntegerType {
            constexpr const char *constructor = "IntegerType.constructor needs to be called with new (external: Napi::External<llvm::IntegerType>)";
            constexpr const char *get = "IntegerType.get needs to be called with: (context: LLVMContext, numBits: number)";
            constexpr const char *isIntegerTy = "IntegerType.isIntegerTy needs to be called with: (bitWidth?: number)";
        }
        namespace FunctionType {
            constexpr const char *constructor = "FunctionType.constructor needs to be called with new (external: Napi::External<llvm::Function>)";
            constexpr const char *get = "FunctionType.get needs to be called with:"
                                        "\n\t - (returnType: Type, isVarArg: boolean)"
                                        "\n\t - (returnType: Type, paramTypes: Type[], isVarArg: boolean)";
        }
        namespace FunctionCallee {
            constexpr const char *constructor = "FunctionCallee.constructor needs to be called with new ()";
        }
        namespace StructType {
            constexpr const char *constructor = "StructType.constructor needs to be called with new (external: Napi::External<llvm::StructType>)";
            constexpr const char *create = "StructType.create needs to be called with:"
                                           "\n\t - (context: LLVMContext, name: string)"
                                           "\n\t - (context: LLVMContext, elementTypes: Type[], name: string)";
            constexpr const char *get = "StructType.get needs to be called with:"
                                        "\n\t - (context: LLVMContext)"
                                        "\n\t - (context: LLVMContext, elementTypes: Type[])";
            constexpr const char *getTypeByName = "StructType.getTypeByName needs to be called with: (context: LLVMContext, name: string)";
            constexpr const char *setBody = "StructType.setBody needs to be called with (elementTypes: Type[])";
            constexpr const char *setName = "StructType.setName needs to be called with (name: string)";
            constexpr const char *getPointerTo = "StructType.getPointer needs to called with: (addrSpace?: number)";
        }
        namespace ArrayType {
            constexpr const char *constructor = "ArrayType.constructor needs to be called with new (external: Napi::External<llvm::ArrayType>)";
            constexpr const char *get = "ArrayType.get needs to be called with (elemType: Type, numElements: number)";
            constexpr const char *isValidElementType = "ArrayType.isValidElementType needs to be called with (elemType: Type)";
        }
        namespace VectorType {
            constexpr const char *constructor = "VectorType.constructor needs to be called with new (external: Napi::External<llvm::VectorType>)";
        }
        namespace PointerType {
            constexpr const char *constructor = "PointerType.constructor needs to be called with new (external: Napi::External<llvm::PointerType>)";
            constexpr const char *get = "PointerType.get needs to be called with: (elementType: Type, addrSpace: number)";
            constexpr const char *getUnqual = "PointerType.getUnqual needs to be called with: (elementType: Type)";
        }
        namespace Value {
            constexpr const char *constructor = "Value.constructor needs to be called with new (external: Napi::External<llvm::Value>)";
            constexpr const char *setName = "Value.setName needs to be called with (name: string)";
            constexpr const char *replaceAllUsesWith = "Value.replaceAllUsesWith needs to be called with: (newValue: Value)";
        }
        namespace Argument {
            constexpr const char *constructor = "Argument.constructor needs to be called with"
                                                "\n\t - new (external: Napi::External<llvm::Argument>)"
                                                "\n\t - new (type: Type, name?: string, func?: Function, argNo?: number)";
            constexpr const char *setName = "Argument.setName needs to be called with (name: string)";
        }
        namespace Attribute {
            constexpr const char *constructor = "Attribute.constructor needs to be called with new (context: LLVMContext, kind: Attribute.AttrKind, type?: Type)";
        }
        namespace BasicBlock {
            constexpr const char *constructor = "BasicBlock.constructor needs to be called with new (external: Napi::External<llvm::BasicBlock>)";
            constexpr const char *Create = "BasicBlock.Create needs to be called with: (context: LLVMContext, name?: string, parent?: Function, insertBefore?: BasicBlock)";
            constexpr const char *insertInto = "BasicBlock.insertInto needs to be called with: (parent: Function, insertBefore?: BasicBlock)";
        }
        namespace User {
            constexpr const char *constructor = "User.constructor needs to be called with new (external: Napi::External<llvm::User>)";
            constexpr const char *getOperand = "User.getOperand needs to be called with: (i: number)";
            constexpr const char *setOperand = "User.setOperand needs to be called with: (i: number, value: Value)";
        }
        namespace Constant {
            constexpr const char *constructor = "Constant.constructor needs to be called with new (external: Napi::External<llvm::Constant>)";
            constexpr const char *getNullValue = "Constant.getNullValue needs to be called with: (type: Type)";
            constexpr const char *getAllOnesValue = "Constant.getAllOnesValue needs to be called with: (type: Type)";
        }
        namespace ConstantInt {
            constexpr const char *constructor = "ConstantInt.constructor needs to be called with new (external: Napi::External<llvm::ConstantInt>)";
            constexpr const char *get = "ConstantInt.get needs to be called with"
                                        "\n\t - (context: LLVMContext, value: APInt)"
                                        "\n\t - (type: Type, value: APInt)"
                                        "\n\t - (type: Type, value: number, isSigned?: boolean)"
                                        "\n\t - (type: IntegerType, value: number, isSigned?: boolean)";
        }
        namespace ConstantFP {
            constexpr const char *constructor = "ConstantFP.constructor needs to be called with new (external: Napi::External<llvm::ConstantFP>)";
            constexpr const char *get = "ConstantFP.get needs to be called with:"
                                        "\n\t - (type: Type, value: number)"
                                        "\n\t - (type: Type, value: APFloat)"
                                        "\n\t - (type: Type, value: string)"
                                        "\n\t - (context: LLVMContext, value: APFloat)";
            constexpr const char *getNaN = "ConstantFP.getNaN need to be called with (type: Type)";
        }
        namespace ConstantArray {
            constexpr const char *constructor = "ConstantArray.constructor needs to be called with new (external: Napi::External<llvm::ConstantArray>)";
            constexpr const char *get = "ConstantArray.get needs to be called with (type: ArrayType, values: Constant[])";
        }
        namespace ConstantStruct {
            constexpr const char *constructor = "ConstantStruct.constructor needs to be called with new (external: Napi::External<llvm::ConstantStruct>)";
            constexpr const char *get = "ConstantStruct.get needs to be called with (type: StructType, values: Constant[])";
        }
        namespace ConstantPointerNull {
            constexpr const char *constructor = "ConstantPointerNull.constructor needs to be called with new (external: Napi::External<llvm::ConstantPointerNull>)";
            constexpr const char *get = "ConstantPointerNull.get needs to be called with (type: PointerType)";
        }
        namespace ConstantDataArray {
            constexpr const char *constructor = "ConstantDataArray.constructor needs to be called with new (external: Napi::External<llvm::ConstantDataArray>)";
            constexpr const char *get = "ConstantArray.get needs to be called with (context: LLVMContext, elements: number[])";
            constexpr const char *getString = "ConstantArray.getString needs to be called with (context: LLVMContext, initializer: string, addNull?: boolean)";
        }
        namespace ConstantExpr {
            constexpr const char *constructor = "ConstantExpr.constructor needs to be called with new (external: Napi::External<llvm::ConstantExpr>)";
            constexpr const char *getBitCast = "ConstantExpr.getBitCast needs to be called with (constant: Constant, type: Type)";
        }
        namespace UndefValue {
            constexpr const char *constructor = "UndefValue.constructor needs to be called with new (external: Napi::External<llvm::UndefValue>)";
            constexpr const char *get = "UndefValue.get needs to be called with (type: Type)";
        }
        namespace GlobalValue {
            constexpr const char *constructor = "GlobalValue.constructor needs to be called with new (external: Napi::External<llvm::GlobalValue>)";
        }
        namespace GlobalObject {
            constexpr const char *constructor = "GlobalObject.constructor needs to be called with new (external: Napi::External<llvm::GlobalObject>)";
        }
        namespace GlobalVariable {
            constexpr const char *constructor = "GlobalVariable.constructor needs to be called with"
                                                "\n\t - new (external: Napi::External<llvm::GlobalVariable>)"
                                                "\n\t - new (type: Type, isConstant: boolean, linkage: LinkageTypes, initializer?: Constant, name?: string)"
                                                "\n\t - new (module: Module, type: Type, isConstant: boolean, linkage: LinkageTypes, initializer: Constant, name?: string)";
            constexpr const char *setInitializer = "GlobalVariable.setInitializer needs to be called with (initVal: Constant | null)";
            constexpr const char *addDebugInfo = "GlobalVariable.addDebugInfo needs to be called with (gv: DIGlobalVariableExpression)";
        }
        namespace Function {
            constexpr const char *constructor = "Function.constructor needs to be called with new (external: Napi::External<llvm::Function>)";
            constexpr const char *Create = "Function.Create needs to be called with: (funcType: FunctionType, linkage: number, name?: string, module?: Module)";
            constexpr const char *getArg = "Function.getArg needs to be called with (i: number)";
            constexpr const char *addBasicBlock = "Function.addBasicBlock needs to be called with (basicBlock: BasicBlock)";
            constexpr const char *insertAfter = "Function.insertAfter needs to be called with (where: BasicBlock, basicBlock: BasicBlock)";
            constexpr const char *setPersonalityFn = "Function.setPersonalityFn needs to be called with (fn: Constant)";
            constexpr const char *setSubprogram = "Function.setSubprogram needs to be called with (subprogram: DISubprogram)";
            constexpr const char *addFnAttr = "Function.addFnAttr needs to be called with (attribute: Attribute)";
            constexpr const char *addParamAttr = "Function.addParamAttr needs to be called with (argNo: number, attribute: Attribute)";
            constexpr const char *addRetAttr = "Function.addRetAttr needs to be called with (attribute: Attribute)";
        }
        namespace Instruction {
            constexpr const char *constructor = "Instruction.constructor needs to be called with new (external: Napi::External<llvm::Instruction>)";
            constexpr const char *setDebugLoc = "Instruction.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace AllocaInst {
            constexpr const char *constructor = "AllocaInst.constructor needs to be called with new (external: Napi::External<llvm::AllocaInst>)";
            constexpr const char *setDebugLoc = "AllocaInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace LoadInst {
            constexpr const char *constructor = "LoadInst.constructor needs to be called with new (external: Napi::External<llvm::LoadInst>)";
            constexpr const char *setDebugLoc = "LoadInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace StoreInst {
            constexpr const char *constructor = "StoreInst.constructor needs to be called with new (external: Napi::External<llvm::StoreInst>)";
            constexpr const char *setDebugLoc = "StoreInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FenceInst {
            constexpr const char *constructor = "FenceInst.constructor needs to be called with new (external: Napi::External<llvm::FenceInst>)";
            constexpr const char *setDebugLoc = "FenceInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace AtomicCmpXchgInst {
            constexpr const char *constructor = "AtomicCmpXchgInst.constructor needs to be called with new (external: Napi::External<llvm::AtomicCmpXchgInst>)";
            constexpr const char *setDebugLoc = "AtomicCmpXchgInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace AtomicRMWInst {
            constexpr const char *constructor = "AtomicRMWInst.constructor needs to be called with new (external: Napi::External<llvm::AtomicRMWInst>)";
            constexpr const char *setDebugLoc = "AtomicRMWInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace GetElementPtrInst {
            constexpr const char *constructor = "GetElementPtrInst.constructor needs to be called with new (external: Napi::External<llvm::GetElementPtrInst>)";
            constexpr const char *setDebugLoc = "GetElementPtrInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ICmpInst {
            constexpr const char *constructor = "ICmpInst.constructor needs to be called with new (external: Napi::External<llvm::ICmpInst>)";
            constexpr const char *setDebugLoc = "ICmpInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FCmpInst {
            constexpr const char *constructor = "FCmpInst.constructor needs to be called with new (external: Napi::External<llvm::FCmpInst>)";
            constexpr const char *setDebugLoc = "FCmpInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CallInst {
            constexpr const char *constructor = "CallInst.constructor needs to be called with new (external: Napi::External<llvm::CallInst>)";
            constexpr const char *setDebugLoc = "CallInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace SelectInst {
            constexpr const char *constructor = "SelectInst.constructor needs to be called with new (external: Napi::External<llvm::SelectInst>)";
            constexpr const char *setCondition = "SelectInst.setCondition needs to be called with (value: Value)";
            constexpr const char *setTrueValue = "SelectInst.setTrueValue needs to be called with (value: Value)";
            constexpr const char *setFalseValue = "SelectInst.setFalseValue needs to be called with (value: Value)";
            constexpr const char *setDebugLoc = "SelectInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace VAArgInst {
            constexpr const char *constructor = "VAArgInst.constructor needs to be called with new (external: Napi::External<llvm::VAArgInst>)";
            constexpr const char *setDebugLoc = "VAArgInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ExtractElementInst {
            constexpr const char *constructor = "ExtractElementInst.constructor needs to be called with new (external: Napi::External<llvm::ExtractElementInst>)";
            constexpr const char *setDebugLoc = "ExtractElementInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace InsertElementInst {
            constexpr const char *constructor = "InsertElementInst.constructor needs to be called with new (external: Napi::External<llvm::InsertElementInst>)";
            constexpr const char *setDebugLoc = "InsertElementInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ShuffleVectorInst {
            constexpr const char *constructor = "ShuffleVectorInst.constructor needs to be called with new (external: Napi::External<llvm::ShuffleVectorInst>)";
            constexpr const char *setDebugLoc = "ShuffleVectorInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ExtractValueInst {
            constexpr const char *constructor = "ExtractValueInst.constructor needs to be called with new (external: Napi::External<llvm::ExtractValueInst>)";
            constexpr const char *setDebugLoc = "ExtractValueInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace InsertValueInst {
            constexpr const char *constructor = "InsertValueInst.constructor needs to be called with new (external: Napi::External<llvm::InsertValueInst>)";
            constexpr const char *setDebugLoc = "InsertValueInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace PHINode {
            constexpr const char *constructor = "PHINode.constructor needs to be called with new (external: Napi::External<llvm::PHINode>)";
            constexpr const char *addIncoming = "PHINode.addIncoming needs to be called with (value: Value, basicBlock: BasicBlock)";
            constexpr const char *setDebugLoc = "PHINode.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace LandingPadInst {
            constexpr const char *constructor = "LandingPadInst.constructor needs to be called with new (external: Napi::External<llvm::LandingPadInst>)";
            constexpr const char *setCleanup = "LandingPadInst.setCleanup needs to be called with (value: boolean)";
            constexpr const char *addClause = "LandingPadInst.addClause needs to be called with (clauseVal: Constant)";
            constexpr const char *setDebugLoc = "LandingPadInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ReturnInst {
            constexpr const char *constructor = "ReturnInst.constructor needs to be called with new (external: Napi::External<llvm::ReturnInst>)";
            constexpr const char *setDebugLoc = "ReturnInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace BranchInst {
            constexpr const char *constructor = "BranchInst.constructor needs to be called with new (external: Napi::External<llvm::BranchInst>)";
            constexpr const char *getSuccessor = "BranchInst.getSuccessor needs to be called with (i: number)";
            constexpr const char *setDebugLoc = "BranchInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace SwitchInst {
            constexpr const char *constructor = "SwitchInst.constructor needs to be called with new (external: Napi::External<llvm::SwitchInst>)";
            constexpr const char *addCase = "SwitchInst.addCase needs to be called with (onVal: ConstantInt, dest: BasicBlock)";
            constexpr const char *setDebugLoc = "SwitchInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace IndirectBrInst {
            constexpr const char *constructor = "IndirectBrInst.constructor needs to be called with new (external: Napi::External<llvm::IndirectBrInst>)";
            constexpr const char *setDebugLoc = "IndirectBrInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace InvokeInst {
            constexpr const char *constructor = "InvokeInst.constructor needs to be called with new (external: Napi::External<llvm::InvokeInst>)";
            constexpr const char *setDebugLoc = "InvokeInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CallBrInst {
            constexpr const char *constructor = "CallBrInst.constructor needs to be called with new (external: Napi::External<llvm::CallBrInst>)";
            constexpr const char *setDebugLoc = "CallBrInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ResumeInst {
            constexpr const char *constructor = "ResumeInst.constructor needs to be called with new (external: Napi::External<llvm::ResumeInst>)";
            constexpr const char *setDebugLoc = "ResumeInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CatchSwitchInst {
            constexpr const char *constructor = "CatchSwitchInst.constructor needs to be called with new (external: Napi::External<llvm::CatchSwitchInst>)";
            constexpr const char *setDebugLoc = "CatchSwitchInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CleanupPadInst {
            constexpr const char *constructor = "CleanupPadInst.constructor needs to be called with new (external: Napi::External<llvm::CleanupPadInst>)";
            constexpr const char *setDebugLoc = "CleanupPadInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CatchPadInst {
            constexpr const char *constructor = "CatchPadInst.constructor needs to be called with new (external: Napi::External<llvm::CatchPadInst>)";
            constexpr const char *setDebugLoc = "CatchPadInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CatchReturnInst {
            constexpr const char *constructor = "CatchReturnInst.constructor needs to be called with new (external: Napi::External<llvm::CatchReturnInst>)";
            constexpr const char *setDebugLoc = "CatchReturnInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace CleanupReturnInst {
            constexpr const char *constructor = "CleanupReturnInst.constructor needs to be called with new (external: Napi::External<llvm::CleanupReturnInst>)";
            constexpr const char *setDebugLoc = "CleanupReturnInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace UnreachableInst {
            constexpr const char *constructor = "UnreachableInst.constructor needs to be called with new (external: Napi::External<llvm::UnreachableInst>)";
            constexpr const char *setDebugLoc = "UnreachableInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace TruncInst {
            constexpr const char *constructor = "TruncInst.constructor needs to be called with new (external: Napi::External<llvm::TruncInst>)";
            constexpr const char *setDebugLoc = "TruncInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace ZExtInst {
            constexpr const char *constructor = "ZExtInst.constructor needs to be called with new (external: Napi::External<llvm::ZExtInst>)";
            constexpr const char *setDebugLoc = "ZExtInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace SExtInst {
            constexpr const char *constructor = "SExtInst.constructor needs to be called with new (external: Napi::External<llvm::SExtInst>)";
            constexpr const char *setDebugLoc = "SExtInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FPTruncInst {
            constexpr const char *constructor = "FPTruncInst.constructor needs to be called with new (external: Napi::External<llvm::FPTruncInst>)";
            constexpr const char *setDebugLoc = "FPTruncInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FPExtInst {
            constexpr const char *constructor = "FPExtInst.constructor needs to be called with new (external: Napi::External<llvm::FPExtInst>)";
            constexpr const char *setDebugLoc = "FPExtInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace UIToFPInst {
            constexpr const char *constructor = "UIToFPInst.constructor needs to be called with new (external: Napi::External<llvm::UIToFPInst>)";
            constexpr const char *setDebugLoc = "UIToFPInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace SIToFPInst {
            constexpr const char *constructor = "SIToFPInst.constructor needs to be called with new (external: Napi::External<llvm::SIToFPInst>)";
            constexpr const char *setDebugLoc = "SIToFPInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FPToUIInst {
            constexpr const char *constructor = "FPToUIInst.constructor needs to be called with new (external: Napi::External<llvm::FPToUIInst>)";
            constexpr const char *setDebugLoc = "FPToUIInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FPToSIInst {
            constexpr const char *constructor = "FPToSIInst.constructor needs to be called with new (external: Napi::External<llvm::FPToSIInst>)";
            constexpr const char *setDebugLoc = "FPToSIInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace IntToPtrInst {
            constexpr const char *constructor = "IntToPtrInst.constructor needs to be called with new (external: Napi::External<llvm::IntToPtrInst>)";
            constexpr const char *setDebugLoc = "IntToPtrInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace PtrToIntInst {
            constexpr const char *constructor = "PtrToIntInst.constructor needs to be called with new (external: Napi::External<llvm::PtrToIntInst>)";
            constexpr const char *setDebugLoc = "PtrToIntInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace BitCastInst {
            constexpr const char *constructor = "BitCastInst.constructor needs to be called with new (external: Napi::External<llvm::BitCastInst>)";
            constexpr const char *setDebugLoc = "BitCastInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace AddrSpaceCastInst {
            constexpr const char *constructor = "AddrSpaceCastInst.constructor needs to be called with new (external: Napi::External<llvm::AddrSpaceCastInst>)";
            constexpr const char *setDebugLoc = "AddrSpaceCastInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace FreezeInst {
            constexpr const char *constructor = "FreezeInst.constructor needs to be called with new (external: Napi::External<llvm::FreezeInst>)";
            constexpr const char *setDebugLoc = "FreezeInst.setDebugLoc needs to be called with: (location: DebugLoc)";
        }
        namespace IRBuilder {
            constexpr const char *constructor = "IRBuilder.constructor needs to be called with:"
                                                "\n\t - new (theBB: BasicBlock)"
                                                "\n\t - new (context: LLVMContext)"
                                                "\n\t - new (ip: Instruction)";
            namespace InsertPoint {
                constexpr const char *constructor = "IRBuilder.InsertPoint.constructor needs to be called with new ()";
            }
            constexpr const char *SetInsertPoint = "IRBuilder.SetInsertPoint needs to be called with:"
                                                   "\n\t - (basicBlock: BasicBlock)"
                                                   "\n\t - (inst: Instruction)";
            constexpr const char *SetCurrentDebugLocation = "IRBuilder.SetCurrentDebugLocation needs to be called with:"
                                                            "\n\t - (location: DebugLoc)"
                                                            "\n\t - (location: DILocation)";
            constexpr const char *restoreIP = "IRBuilder.restoreIP needs to be called with (ip: IRBuilder.InsertPoint)";
            constexpr const char *CreateGlobalString = "IRBuilder.CreateGlobalString needs to be called with (str: string, name?: string, addrSpace?: number, module?: Module)";

            constexpr const char *getInt1 = "IRBuilder.getInt1 needs to be called with (value: boolean)";
            constexpr const char *getIntFactory = "IRBuilder.[getIntX] needs to be called with (value: number)";
            constexpr const char *getIntN = "IRBuilder.getIntN needs to be called with (numBits: number, value: number)";
            constexpr const char *getInt = "IRBuilder.getInt needs to be called with (value: APInt)";

            constexpr const char *getIntNTy = "IRBuilder.getIntNTy needs to be called with (numBits: number)";
            constexpr const char *getInt8PtrTy = "IRBuilder.getInt8PtrTy needs to be called with (addrSpace?: number)";
            constexpr const char *getIntPtrTy = "IRBuilder.getIntPtrTy needs to be called with (dataLayout: DataLayout, addrSpace?: number)";

            constexpr const char *CreateRet = "IRBuilder.CreateRet needs to be called with: (value: Value)";
            constexpr const char *CreateBr = "IRBuilder.CreateBr needs to be called with: (destBB: BasicBlock)";
            constexpr const char *CreateCondBr = "IRBuilder.CreateCondBr needs to be called with: (cond: Value, thenBB: BasicBlock, elseBB: BasicBlock)";
            constexpr const char *CreateSwitch = "IRBuilder.CreateSwitch needs to be called with: (value: Value, dest: BasicBlock, numCases?: number)";
            constexpr const char *CreateIndirectBr = "IRBuilder.CreateIndirectBr needs to be called with: (addr: Value, numDests?: number)";
            constexpr const char *CreateInvoke = "IRBuilder.CreateInvoke needs to be called with:"
                                                 "\n\t - (callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string)"
                                                 "\n\t - (callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string)"
                                                 "\n\t - (callee: FunctionCallee, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string)"
                                                 "\n\t - (callee: FunctionCallee, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string)"
                                                 "\n\t - (funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string)"
                                                 "\n\t - (funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string)";
            constexpr const char *CreateResume = "IRBuilder.CreateRet needs to be called with: (exn: Value)";

            constexpr const char *CreateBinOpFactory = "IRBuilder.[CreateBinaryOperation] needs to be called with: (lhs: Value, rhs: Value, name?: string)";
            constexpr const char *CreateUnOpFactory = "IRBuilder.[CreateUnaryOperation] needs to be called with: (value: Value, name?: string)";

            constexpr const char *CreateAlloca = "IRBuilder.CreateAlloca needs to be called with: (type: Type, arraySize?: Value, name?: string)";
            constexpr const char *CreateLoad = "IRBuilder.CreateLoad needs to be called with: (type: Type, ptr: Value, name?: string)";
            constexpr const char *CreateStore = "IRBuilder.CreateStore needs to be called with: (value: Value, ptr: Value)";
            constexpr const char *CreateGEP = "IRBuilder.CreateGEP needs to be called with:"
                                              "\n\t - (type: Type, ptr: Value, idxList: Value[], name?: string)"
                                              "\n\t - (type: Type, ptr: Value, idx: Value, name?: string)";
            constexpr const char *CreateInBoundsGEP = "IRBuilder.CreateInBoundsGEP needs to be called with:"
                                                      "\n\t - (type: Type, ptr: Value, idxList: Value[], name?: string)"
                                                      "\n\t - (type: Type, ptr: Value, idx: Value, name?: string)";
            constexpr const char *CreateGlobalStringPtr = "IRBuilder.CreateGlobalStringPtr needs to be called with (str: string, name?: string, addrSpace?: number, module?: Module)";

            constexpr const char *CreateCastFactory = "IRBuilder.[CreateCast] needs to be called with (value: Value, destType: Type, name?: string)";
            constexpr const char *CreateIntCast = "IRBuilder.CreateIntCast needs to be called with (value: Value, destType: Type, isSigned: boolean, name?: string)";

            constexpr const char *CreatePHI = "IRBuilder.CreatePHI needs to be called with: (type: Type, numReservedValues: number, name?: string)";
            constexpr const char *CreateCall = "IRBuilder.CreateCall needs to be called with:"
                                               "\n\t - (callee: Function, name?: string)"
                                               "\n\t - (callee: Function, args: Value[], name?: string)"
                                               "\n\t - (callee: FunctionCallee, name?: string)"
                                               "\n\t - (callee: FunctionCallee, args: Value[], name?: string)"
                                               "\n\t - (funcType: FunctionType, callee: Value, name?: string)"
                                               "\n\t - (funcType: FunctionType, callee: Value, args: Value[], name?: string)";
            constexpr const char *CreateSelect = "IRBuilder.CreateSelect needs to be called with (cond: Value, trueValue: Value, falseValue: Value, name?: string)";
            constexpr const char *CreateExtractValue = "IRBuilder.CreateExtractValue needs to be called with (agg: Value, idxs: number[], name?: string)";
            constexpr const char *CreateInsertValue = "IRBuilder.CreateInsertValue needs to be called with (agg: Value, value: Value, idxs: number[], name?: string)";
            constexpr const char *CreateLandingPad = "IRBuilder.CreateLandingPad needs to be called with (type: Type, numClauses: number, name?: string)";
            constexpr const char *CreatePtrDiff = "IRBuilder.CreatePtrDiff needs to be called with (elemType: Type, lhs: Value, rhs: Value, name?: string)";
        }
        namespace Metadata {
            constexpr const char *constructor = "Metadata.constructor needs to be called with new (external: Napi::External<llvm::Metadata>)";
        }
        namespace MDNode {
            constexpr const char *constructor = "MDNode.constructor needs to be called with new (external: Napi::External<llvm::MDNode>)";
        }
        namespace DebugLoc {
            constexpr const char *constructor = "DebugLoc.constructor needs to be called with:"
                                                "\n\t - new (external: Napi::External<llvm::DebugLoc>)"
                                                "\n\t - new ()";
        }
        namespace DITypeRefArray {
            constexpr const char *constructor = "DITypeRefArray.constructor needs to be called with new (external: Napi::External<llvm::DITypeRefArray>)";
        }
        namespace DINode {
            constexpr const char *constructor = "DINode.constructor needs to be called with new (external: Napi::External<llvm::DINode>)";
        }
        namespace DIScope {
            constexpr const char *constructor = "DIScope.constructor needs to be called with new (external: Napi::External<llvm::DIScope>)";
        }
        namespace DIFile {
            constexpr const char *constructor = "DIFile.constructor needs to be called with new (external: Napi::External<llvm::DIFile>)";
        }
        namespace DIType {
            constexpr const char *constructor = "DIType.constructor needs to be called with new (external: Napi::External<llvm::DIType>)";
        }
        namespace DIBasicType {
            constexpr const char *constructor = "DIBasicType.constructor needs to be called with new (external: Napi::External<llvm::DIBasicType>)";
        }
        namespace DIDerivedType {
            constexpr const char *constructor = "DIDerivedType.constructor needs to be called with new (external: Napi::External<llvm::DIDerivedType>)";
        }
        namespace DICompositeType {
            constexpr const char *constructor = "DICompositeType.constructor needs to be called with new (external: Napi::External<llvm::DICompositeType>)";
        }
        namespace DISubroutineType {
            constexpr const char *constructor = "DISubroutineType.constructor needs to be called with new (external: Napi::External<llvm::DISubroutineType>)";
        }
        namespace DICompileUnit {
            constexpr const char *constructor = "DICompileUnit.constructor needs to be called with new (external: Napi::External<llvm::DICompileUnit>)";
        }
        namespace DILocalScope {
            constexpr const char *constructor = "DILocalScope.constructor needs to be called with new (external: Napi::External<llvm::DILocalScope>)";
        }
        namespace DILocation {
            constexpr const char *constructor = "DILocation.constructor needs to be called with new (external: Napi::External<llvm::DILocation>)";
            constexpr const char *get = "DILocation.get needs to be called with:"
                                        "\n\t - (context: LLVMContext, line: number, column: number, metadata: Metadata)"
                                        "\n\t - (context: LLVMContext, line: number, column: number, scope: DILocalScope)";
        }
        namespace DISubprogram {
            constexpr const char *constructor = "DISubprogram.constructor needs to be called with new (external: Napi::External<llvm::DISubprogram>)";
        }
        namespace DILexicalBlock {
            constexpr const char *constructor = "DILexicalBlock.constructor needs to be called with new (external: Napi::External<llvm::DILexicalBlock>)";
        }
        namespace DINamespace {
            constexpr const char *constructor = "DINamespace.constructor needs to be called with new (external: Napi::External<llvm::DINamespace>)";
        }
        namespace DIVariable {
            constexpr const char *constructor = "DIVariable.constructor needs to be called with new (external: Napi::External<llvm::DIVariable>)";
        }
        namespace DIExpression {
            constexpr const char *constructor = "DIExpression.constructor needs to be called with new (external: Napi::External<llvm::DIExpression>)";
        }
        namespace DIGlobalVariableExpression {
            constexpr const char *constructor = "DIGlobalVariableExpression.constructor needs to be called with new (external: Napi::External<llvm::DIGlobalVariableExpression>)";
        }
        namespace DILocalVariable {
            constexpr const char *constructor = "DILocalVariable.constructor needs to be called with new (external: Napi::External<llvm::DILocalVariable>)";
        }
        namespace DIGlobalVariable {
            constexpr const char *constructor = "DIGlobalVariable.constructor needs to be called with new (external: Napi::External<llvm::DIGlobalVariable>)";
        }
        namespace DIBuilder {
            constexpr const char *constructor = "DIBuilder.constructor needs to be called with:"
                                                "\n\t - new (external: Napi::External<llvm::DIBuilder>)"
                                                "\n\t - new (module: Module)";
            constexpr const char *createFile = "DIBuilder.createFile needs to be called with (filename: string, directory: string)";
            constexpr const char *createCompileUnit = "DIBuilder.createCompileUnit needs to be called with (lang: number, file: DIFile, producer: string, isOptimized: boolean, flags: string, rv: number)";
            constexpr const char *createFunction = "DIBuilder.createFunction needs to be called with: (scope: DIScope, name: string, linkage: string, file: DIFile, line: number, type: DISubroutineType, scopeLine: number, flags: number, spFlags: number)";
            constexpr const char *createLexicalBlock = "DIBuilder.createLexicalBlock needs to be called with: (scope: DIScope, file: DIFile, line: number, column: number)";
            constexpr const char *createBasicType = "DIBuilder.createBasicType needs to be called with (name: string, sizeInBits: number, encoding: number)";
            constexpr const char *getOrCreateTypeArray = "DIBuilder.getOrCreateTypeArray needs to be called with (elements: Metadata[])";
            constexpr const char *createSubroutineType = "DIBuilder.createSubroutineType needs to be called with (paramTypes: DITypeRefArray)";
            constexpr const char *createParameterVariable = "DIBuilder.createParameterVariable needs to be called with (scope: DIScope, name: string, argNo: number, file: DIFile, line: number, type: DIType, alwaysPreserve?: boolean)";
            constexpr const char *createAutoVariable = "DIBuilder.createAutoVariable needs to be called with (scope: DIScope, name: string, file: DIFile, line: number, type: DIType, alwaysPreserve?: boolean)";
            constexpr const char *createGlobalVariableExpression = "DIBuilder.createGlobalVariableExpression needs to be called with (context: DIScope, name: string, linkage: string, file: DIFile, line: number, type: DIType, IsLocalToUnit: boolean)";
            constexpr const char *insertDeclare = "DIBuilder.insertDeclare needs to be called with:"
                                                  "\n\t - (storage: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBB: BasicBlock)"
                                                  "\n\t - (storage: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBefore: Instruction)";
            constexpr const char *insertDbgValueIntrinsic = "DIBuilder.insertDbgValueIntrinsic needs to be called with:"
                                                            "\n\t - (value: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBB: BasicBlock)"
                                                            "\n\t - (value: Value, variable: DILocalVariable, expr: DIExpression, location: DILocation, insertBefore: Instruction)";;
            constexpr const char *finalizeSubprogram = "DIBuilder.finalizeSubprogram needs to be called with (subprogram: DISubprogram)";
        }
        namespace DataLayout {
            constexpr const char *constructor = "DataLayout.constructor needs to be called with"
                                                "\n\t - new (external: Napi::External<llvm::DataLayout>)"
                                                "\n\t - new (desc: string)";
            constexpr const char *getTypeAllocSize = "DataLayout.getTypeAllocSize needs to be called with (type: Type)";
        }
        namespace Linker {
            constexpr const char *constructor = "Linker.constructor needs to be called with: new (module: Module)";
            constexpr const char *linkInModule = "Linker.linkInModule needs to be called with (src: Module)";
            constexpr const char *linkModules = "Linker.linkModules needs to be called with (dest: Module, src: Module)";
        }
        namespace SMDiagnostic {
            constexpr const char *constructor = "SMDiagnostic.constructor needs to be called with new ()";
        }
        namespace Target {
            constexpr const char *constructor = "Target.constructor needs to be called with new (external: Napi::External<llvm::Target>)";
            constexpr const char *createTargetMachine = "Target.createTargetMachine needs to be called with (targetTriple: string, cpu: string, features?: string)";
        }
        namespace TargetRegistry {
            constexpr const char *lookupTarget = "TargetRegistry.lookupTarget needs to be called with (triple: string)";
        }
        namespace TargetMachine {
            constexpr const char *constructor = "TargetMachine.constructor needs to be called with new (external: Napi::External<llvm::TargetMachine>)";
        }
    }
    namespace Namespace::Intrinsic {
        constexpr const char *getDeclaration = "Intrinsic.getDeclaration needs to be called with: (module: Module, id: number, types?: [])";
    }
    namespace Function {
        constexpr const char *WriteBitcodeToFile = "WriteBitcodeToFile needs to be called with: (module: Module, filename: string)";
        constexpr const char *verifyFunction = "verifyFunction needs to be called with (func: Function)";
        constexpr const char *verifyModule = "verifyModule needs to be called with (module: Module)";
        constexpr const char *parseIRFile = "parseIRFile needs to be called with (filename: string, err: SMDiagnostic, context: LLVMContext)";
    }
}
