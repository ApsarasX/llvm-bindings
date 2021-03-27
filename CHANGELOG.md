## [0.0.4](https://github.com/ApsarasX/llvm-bindings/compare/v0.0.3...v0.0.4) (2021-03-27)



## [0.0.3](https://github.com/ApsarasX/llvm-bindings/compare/v0.0.2...v0.0.3) (2021-03-27)


### Bug Fixes

* **Bitcode:** correct name of function WriteBitcodeToFile and make up its signature ([3e7bfe5](https://github.com/ApsarasX/llvm-bindings/commit/3e7bfe5a261208515690ee0b80fc551a1e1650e5))


### Features

* **IR:** add Class ArrayType ([4c2c174](https://github.com/ApsarasX/llvm-bindings/commit/4c2c17480e09553d9a83f6c24f44c099d555a9af))
* **IR:** add Class ConstantPointerNull ([aedc714](https://github.com/ApsarasX/llvm-bindings/commit/aedc714c95db99659aebc523782d350f282e5dc2))
* **IR:** add Class SMDiagnostic and Function parseIRFile ([073e9f3](https://github.com/ApsarasX/llvm-bindings/commit/073e9f35bc8cb72b69eee23649d91ff09afcf940))



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