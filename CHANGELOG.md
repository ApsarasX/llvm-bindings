## 0.0.2 (2021-03-26)

### Features

- add Class Argument
- add ConstantFP.getNaN
- add Function.arg_size and Function.getArg
- delete Class FunctionCallee
- supplement more APIs of Class IRBuilder
- add more test cases
- add type signature for new APIs


## 0.0.1 (2021-03-26)

This is the first release of `llvm-bindings`.

And in this version, `llvm-bindings` has supported some of high frequency used APIs of LLVM.

The specific classes and functions supported by the version are as follows:

- **ADT:** `APInt` `APFloat`
- **Bitcode:** `writeBitcodeToFile`
- **IR:** `LLVMContext` `Module` `Type` `IntegerType` `PointerType` `FunctionType` `StructType` `Value` `User` `Constant` `ConstantInt` `ConstantFP` `GlobalValue` `GlobalObject` `GlobalVariable` `Function` `BasicBlock` `FunctionCallee` `IRBuilder`
- **Support:** `Target` `TargetRegistry.lookupTarget` `initializeAllTargetInfos` `initializeAllTargets` `initializeAllTargetMCs` `initializeAllAsmParsers` `initializeAllAsmPrinters`
- **Target:** `TargetMachine`