#pragma once

namespace ErrMsg {
    namespace Class {
        namespace APFloat {
            static const char *constructor = "APFloat.constructor needs to be called with new (value: number)";
        }
        namespace APInt {
            static const char *constructor = "APInt.constructor needs to be called with new (numBits: number, value: number, isSigned?: boolean)";
        }
        namespace AllocaInst {
            static const char *constructor = "AllocaInst.constructor needs to be called with new (external: Napi::External<llvm::AllocaInst>)";
        }
        namespace Argument {
            static const char *constructor = "Argument.constructor needs to be called with"
                                             "\n\t - new (external: Napi::External<llvm::Argument>)"
                                             "\n\t - new (type: Type, name?: string, func?: Function, argNo?: number)";
            static const char *setName = "Argument.setName needs to be called with (name: string)";
        }
        namespace ArrayType {
            static const char *constructor = "ArrayType.constructor needs to be called with new (external: Napi::External<llvm::ArrayType>)";
            static const char *get = "ArrayType.get needs to be called with (elemType: Type, numElements: number)";
            static const char *isValidElementType = "ArrayType.isValidElementType needs to be called with (elemType: Type)";
        }
        namespace BasicBlock {
            static const char *constructor = "BasicBlock.constructor needs to be called with new (external: Napi::External<llvm::BasicBlock>)";
            static const char *Create = "BasicBlock.Create needs to be called with: (context: LLVMContext, name?: string, parent?: Function, insertBefore?: BasicBlock)";
        }
        namespace BranchInst {
            static const char *constructor = "BranchInst.constructor needs to be called with new (external: Napi::External<llvm::BranchInst>)";
            static const char *getSuccessor = "BranchInst.getSuccessor needs to be called with (i: number)";
        }
        namespace CallInst {
            static const char *constructor = "CallInst.constructor needs to be called with new (external: Napi::External<llvm::CallInst>)";
        }
        namespace InvokeInst {
            static const char *constructor = "InvokeInst.constructor needs to be called with new (external: Napi::External<llvm::InvokeInst>)";
        }
        namespace Constant {
            static const char *constructor = "Constant.constructor needs to be called with new (external: Napi::External<llvm::Constant>)";
            static const char *getNullValue = "Constant.getNullValue needs to be called with: (type: Type)";
            static const char *getAllOnesValue = "Constant.getAllOnesValue needs to be called with: (type: Type)";
        }
        namespace ConstantFP {
            static const char *constructor = "ConstantFP.constructor needs to be called with new (external: Napi::External<llvm::ConstantFP>)";
            static const char *get = "ConstantFP.get needs to be called with:"
                                     "\n\t - (type: Type, value: number)"
                                     "\n\t - (type: Type, value: APFloat)"
                                     "\n\t - (type: Type, value: string)"
                                     "\n\t - (context: LLVMContext, value: APFloat)";
            static const char *getNaN = "ConstantFP.getNaN need to be called with (type: Type)";
        }
        namespace ConstantInt {
            static const char *constructor = "ConstantInt.constructor needs to be called with new (external: Napi::External<llvm::ConstantInt>)";
            static const char *get = "ConstantInt.get needs to be called with"
                                     "\n\t - (context: LLVMContext, value: APInt)"
                                     "\n\t - (type: Type, value: APInt)"
                                     "\n\t - (type: Type, value: number, isSigned?: boolean)"
                                     "\n\t - (type: IntegerType, value: number, isSigned?: boolean)";
        }
        namespace ConstantPointerNull {
            static const char *constructor = "ConstantPointerNull.constructor needs to be called with new (external: Napi::External<llvm::ConstantPointerNull>)";
            static const char *get = "ConstantPointerNull.get needs to be called with (type: PointerType)";
        }
        namespace ConstantStruct {
            static const char *constructor = "ConstantStruct.constructor needs to be called with new (external: Napi::External<llvm::ConstantPointerNull>)";
            static const char *get = "ConstantStruct.get needs to be called with (type: StructType, values: Constant[])";
        }
        namespace DataLayout {
            static const char *constructor = "DataLayout.constructor needs to be called with"
                                             "\n\t - new (external: Napi::External<llvm::DataLayout>)"
                                             "\n\t - new (desc: string)";
        }
        namespace Function {
            static const char *constructor = "Function.constructor needs to be called with new (external: Napi::External<llvm::Function>)";
            static const char *Create = "Function.Create needs to be called with: (funcType: FunctionType, linkage: number, name?: string, module?: Module)";
            static const char *getArg = "Function.getArg needs to be called with (i: number)";
            static const char *addBasicBlock = "Function.addBasicBlock needs to be called with (basicBlock: BasicBlock)";
            static const char *insertAfter = "Function.insertAfter needs to be called with (where: BasicBlock, basicBlock: BasicBlock)";
        }
        namespace FunctionCallee {
            static const char *constructor = "FunctionCallee.constructor needs to be called with new ()";
        }
        namespace FunctionType {
            static const char *constructor = "FunctionType.constructor needs to be called with new (external: Napi::External<llvm::Function>)";
            static const char *get = "FunctionType.get needs to be called with:"
                                     "\n\t - (returnType: Type, isVarArg: boolean)"
                                     "\n\t - (returnType: Type, paramTypes: Type[], isVarArg: boolean)";
        }
        namespace GlobalObject {
            static const char *constructor = "GlobalObject.constructor needs to be called with new (external: Napi::External<llvm::GlobalObject>)";
        }
        namespace GlobalValue {
            static const char *constructor = "GlobalValue.constructor needs to be called with new (external: Napi::External<llvm::GlobalValue>)";
        }
        namespace GlobalVariable {
            static const char *constructor = "GlobalVariable.constructor needs to be called with"
                                             "\n\t - new (external: Napi::External<llvm::GlobalVariable>)"
                                             "\n\t - new (type: Type, isConstant: boolean, linkage: LinkageTypes, initializer?: Constant, name?: string)"
                                             "\n\t - new (module: Module, type: Type, isConstant: boolean, linkage: LinkageTypes, initializer: Constant, name?: string)";
        }
        namespace Instruction {
            static const char *constructor = "Instruction.constructor needs to be called with new (external: Napi::External<llvm::Instruction>)";
        }
        namespace IntegerType {
            static const char *constructor = "IntegerType.constructor needs to be called with new (external: Napi::External<llvm::IntegerType>)";
            static const char *get = "IntegerType.get needs to be called with: (context: LLVMContext, numBits: number)";
            static const char *isIntegerTy = "IntegerType.isIntegerTy needs to be called with: (bitWidth?: number)";
        }
        namespace IRBuilder {
            static const char *constructor = "IRBuilder.constructor needs to be called with: new (context: LLVMContext)";
            static const char *CreateBinOpFactory = "IRBuilder.[CreateBinaryOperation] needs to be called with: (lhs: Value, rhs: Value, name?: string)";
            static const char *CreateUnOpFactory = "IRBuilder.[CreateUnaryOperation] needs to be called with: (value: Value, name?: string)";
            static const char *CreateAlloca = "IRBuilder.CreateAlloca needs to be called with: (type: Type, arraySize?: Value, name?: string)";
            static const char *CreateBr = "IRBuilder.CreateBr needs to be called with: (destBB: BasicBlock)";
            static const char *CreateCall = "IRBuilder.CreateCall needs to be called with:"
                                            "\n\t - (callee: Function, name?: string)"
                                            "\n\t - (callee: Function, args: Value[], name?: string)"
                                            "\n\t - (funcType: FunctionType, callee: Value, name?: string)"
                                            "\n\t - (funcType: FunctionType, callee: Value, args: Value[], name?: string)";
            static const char *CreateInvoke = "IRBuilder.CreateInvoke needs to be called with:"
                                              "\n\t - (callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string)"
                                              "\n\t - (callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string)"
                                              "\n\t - (funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, name?: string)"
                                              "\n\t - (funcType: FunctionType, callee: Function, normalDest: BasicBlock, unwindDest: BasicBlock, args: Value[], name?: string)";
            static const char *CreateCondBr = "IRBuilder.CreateCondBr needs to be called with: (cond: Value, thenBB: BasicBlock, elseBB: BasicBlock)";
            static const char *CreateLoad = "IRBuilder.CreateLoad needs to be called with: (type: Type, ptr: Value, name?: string)";
            static const char *CreateRet = "IRBuilder.CreateRet needs to be called with: (value: Value)";
            static const char *CreateSwitch = "IRBuilder.CreateSwitch needs to be called with: (value: Value, dest: BasicBlock, numCases?: number)";
            static const char *CreateStore = "IRBuilder.CreateStore needs to be called with: (value: Value, ptr: Value)";
            static const char *CreateGlobalString = "IRBuilder.CreateGlobalString needs to be called with (str: string, name?: string, addrSpace?: number, module?: Module)";
            static const char *CreateGlobalStringPtr = "IRBuilder.CreateGlobalStringPtr needs to be called with (str: string, name?: string, addrSpace?: number, module?: Module)";
            static const char *CreatePHI = "IRBuilder.CreatePHI needs to be called with: (type: Type, numReservedValues: number, name?: string)";
            static const char *CreateSelect = "IRBuilder.CreateSelect needs to be called with (cond: Value, trueValue: Value, falseValue: Value, name?: string)";
            static const char *CreateExtractValue = "IRBuilder.CreateExtractValue needs to be called with (agg: Value, idxs: number[], name?: string)";
            static const char *CreateInsertValue = "IRBuilder.CreateInsertValue needs to be called with (agg: Value, value: Value, idxs: number[], name?: string)";
            static const char *CreateLandingPad = "IRBuilder.CreateLandingPad needs to be called with (type: Type, numClauses: number, name?: string)";
            static const char *CreateGEP = "IRBuilder.CreateGEP needs to be called with:"
                                           "\n\t - (ptr: Value, idxList: Value[], name?: string)"
                                           "\n\t - (ptr: Value, idx: Value, name?: string)"
                                           "\n\t - (type: Type, ptr: Value, idxList: Value[], name?: string)"
                                           "\n\t - (type: Type, ptr: Value, idx: Value, name?: string)";
            static const char *CreateInBoundsGEP = "IRBuilder.CreateInBoundsGEP needs to be called with:"
                                                   "\n\t - (ptr: Value, idxList: Value[], name?: string)"
                                                   "\n\t - (type: Type, ptr: Value, idxList: Value[], name?: string)"
                                                   "\n\t - (type: Type, ptr: Value, idx: Value, name?: string)";
            static const char *CreateCastFactory = "IRBuilder.[CreateCast] needs to be called with (value: Value, destType: Type, name?: string)";
            static const char *CreateIntCast = "IRBuilder.CreateIntCast needs to be called with (value: Value, destType: Type, isSigned: boolean, name?: string)";
            static const char *getInt1 = "IRBuilder.getInt1 needs to be called with (value: boolean)";
            static const char *getIntFactory = "IRBuilder.[getIntX] needs to be called with (value: number)";
            static const char *getIntN = "IRBuilder.getIntN needs to be called with (n: number, value: number)";
            static const char *getInt = "IRBuilder.getInt needs to be called with (value: APInt)";
            static const char *getIntNTy = "IRBuilder.getIntNTy needs to be called with (n: number)";
            static const char *getInt8PtrTy = "IRBuilder.getInt8PtrTy needs to be called with (addrSpace?: number)";
            static const char *getIntPtrTy = "IRBuilder.getIntPtrTy needs to be called with (dataLayout: DataLayout, addrSpace?: number)";
            static const char *SetInsertPoint = "IRBuilder.SetInsertPoint needs to be called with: (basicBlock: BasicBlock)";
            static const char *restoreIP = "IRBuilder.restoreIP needs to be called with (ip: IRBuilder.InsertPoint)";
            namespace InsertPoint {
                static const char *constructor = "IRBuilder.InsertPoint.constructor needs to be called with new ()";
            }
        }
        namespace LLVMContext {
            static const char *constructor = "LLVMContext.constructor needs to be called with new ()";
        }
        namespace LoadInst {
            static const char *constructor = "LoadInst.constructor needs to be called with new (external: Napi::External<llvm::LoadInst>)";
        }
        namespace Module {
            static const char *constructor = "Module.constructor needs to be called with"
                                             "\n\t - new (external: Napi::External<llvm::Module>)"
                                             "\n\t - new (moduleID: string, context: LLVMContext)";
            static const char *getFunction = "Module.getFunction needs to be called with: (name: string)";
            static const char *getOrInsertFunction = "Module.getOrInsertFunction needs to be called with: (name: string, fnType: FunctionType)";
            static const char *getGlobalVariable = "Module.getGlobalVariable needs to be called with: (name: string, allowInternal?: boolean)";
            static const char *getTypeByName = "Module.getTypeByName needs to be called with: (name: string)";
            static const char *setDataLayout = "Module.setDataLayout needs to be called with:"
                                               "\n\t - (desc: string)"
                                               "\n\t - (dataLayout: DataLayout)";
            static const char *setModuleIdentifier = "Module.setModuleIdentifier needs to be called with: (moduleID: string)";
            static const char *setSourceFileName = "Module.setSourceFileName needs to be called with: (sourceFileName: string)";
            static const char *setTargetTriple = "Module.setTargetTriple needs to be called with: (targetTriple: string)";
            static const char *print = "Module.print needs to be called with (filename?: string)";
        }
        namespace PHINode {
            static const char *constructor = "PHINode.constructor needs to be called with new (external: Napi::External<llvm::PHINode>)";
            static const char *addIncoming = "PHINode.addIncoming needs to be called with (value: Value, basicBlock: BasicBlock)";
        }
        namespace PointerType {
            static const char *constructor = "PointerType.constructor needs to be called with new (external: Napi::External<llvm::PointerType>)";
            static const char *get = "PointerType.get needs to be called with: (elementType: Type, addrSpace: number)";
            static const char *getUnqual = "PointerType.getUnqual needs to be called with: (elementType: Type)";
        }
        namespace ReturnInst {
            static const char *constructor = "ReturnInst.constructor needs to be called with new (external: Napi::External<llvm::ReturnInst>)";
        }
        namespace SwitchInst {
            static const char *constructor = "SwitchInst.constructor needs to be called with new (external: Napi::External<llvm::SwitchInst>)";
            static const char *addCase = "SwitchInst.addCase needs to be called with (onVal: ConstantInt, dest: BasicBlock)";
        }
        namespace StoreInst {
            static const char *constructor = "StoreInst.constructor needs to be called with new (external: Napi::External<llvm::StoreInst>)";
        }
        namespace LandingPadInst {
            static const char *constructor = "LandingPadInst.constructor needs to be called with new (external: Napi::External<llvm::LandingPadInst>)";
            static const char *setCleanup = "LandingPadInst.setCleanup needs to be called with (value: boolean)";
            static const char *addClause = "LandingPadInst.addClause needs to be called with (clauseVal: Constant)";
        }
        namespace UnreachableInst {
            static const char *constructor = "UnreachableInst.constructor needs to be called with new (external: Napi::External<llvm::UnreachableInst>)";
        }
        namespace StructType {
            static const char *constructor = "StructType.constructor needs to be called with new (external: Napi::External<llvm::StructType>)";
            static const char *create = "StructType.create needs to be called with:"
                                        "\n\t - (context: LLVMContext, name: string)"
                                        "\n\t - (context: LLVMContext, elementTypes: Type[], name: string)";
            static const char *setBody = "StructType.setBody needs to be called with (elementTypes: Type[])";
            static const char *getPointerTo = "StructType.getPointer needs to called with: (addrSpace?: number)";
        }
        namespace Type {
            static const char *constructor = "Type.constructor needs to be called with new (external: Napi::External<llvm::Type>)";
            static const char *getPointerTo = "Type.getPointer needs to called with: (addrSpace?: number)";
            static const char *getIntNTy = "Type.getIntNTy needs to be called with: (context: LLVMContext, n: number)";
            static const char *isIntegerTy = "Type.isIntegerTy needs to be called with: (bitWidth?: number)";
            static const char *getTypeFactory = "Type.[getType] needs to be called with (context: LLVMContext)";
            static const char *getIntTypeFactory = "Type.[getIntType] needs to be called with (context: LLVMContext)";
            static const char *getPointerTypeFactory = "Type.[getPointerType] needs to be called with (context: LLVMContext, addrSpace?: number)";
        }
        namespace User {
            static const char *constructor = "User.constructor needs to be called with new (external: Napi::External<llvm::User>)";
            static const char *getOperand = "User.getOperand needs to be called with: (i: number)";
            static const char *setOperand = "User.setOperand needs to be called with: (i: number, value: Value)";
        }
        namespace Value {
            static const char *constructor = "Value.constructor needs to be called with new (external: Napi::External<llvm::Value>)";
            static const char *setName = "Value.setName needs to be called with (name: string)";
            static const char *replaceAllUsesWith = "Value.replaceAllUsesWith needs to be called with: (newValue: Value)";
        }
        namespace SMDiagnostic {
            static const char *constructor = "SMDiagnostic.constructor needs to be called with new ()";
        }
        namespace Target {
            static const char *constructor = "Target.constructor needs to be called with new (external: Napi::External<llvm::Target>)";
            static const char *createTargetMachine = "Target.createTargetMachine needs to be called with (targetTriple: string, cpu: string, features?: string)";
        }
        namespace TargetRegistry {
            static const char *lookupTarget = "TargetRegistry.lookupTarget needs to be called with (triple: string)";
        }
        namespace TargetMachine {
            static const char *constructor = "TargetMachine.constructor needs to be called with new (external: Napi::External<llvm::TargetMachine>)";
        }
        namespace Linker {
            static const char *constructor = "Linker.constructor needs to be called with: new (module: Module)";
            static const char *linkInModule = "Linker.linkInModule needs to be called with (src: Module)";
            static const char *linkModules = "Linker.linkModules needs to be called with (dest: Module, src: Module)";
        }
    }
    namespace Namespace::Intrinsic {
        static const char *getDeclaration = "Intrinsic.getDeclaration needs to be called with: (module: Module, id: number, types?: [])";
    }
    namespace Function {
        static const char *WriteBitcodeToFile = "WriteBitcodeToFile needs to be called with: (module: Module, filename: string)";
        static const char *verifyFunction = "verifyFunction needs to be called with (func: Function)";
        static const char *verifyModule = "verifyModule needs to be called with (module: Module)";
        static const char *parseIRFile = "parseIRFile needs to be called with (filename: string, err: SMDiagnostic, context: LLVMContext)";
    }
}
