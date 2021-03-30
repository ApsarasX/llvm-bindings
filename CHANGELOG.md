## [0.1.5](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.4...v0.1.5) (2021-03-30)


### Features

* **IR:** add more methods for BasicBlock, Function, IRBuilder ([b1266c2](https://github.com/ApsarasX/llvm-bindings/commit/b1266c2bc86152ae4af776c2b9af9ca48dd6b6c3))
* **IR:** add overloading function of Module.print ([f5fe230](https://github.com/ApsarasX/llvm-bindings/commit/f5fe230b754fba7e528241909149314e2bb0cdac))
* **IR:** class Value supports receiving null ([a1fadd5](https://github.com/ApsarasX/llvm-bindings/commit/a1fadd5d3af906612ddb48e8cd9f4e4726a2f06a))



## [0.1.4](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.3...v0.1.4) (2021-03-29)


### Features

* **IR:** add IRBuilder.CreateSelect ([33da3bf](https://github.com/ApsarasX/llvm-bindings/commit/33da3bf868d751f89aca2266cfcb8b102ac4d2d9))



## [0.1.3](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.2...v0.1.3) (2021-03-29)


### Bug Fixes

* **IR:** fix the parameter verification problem of IRBuilder.CreateLoad ([df2b800](https://github.com/ApsarasX/llvm-bindings/commit/df2b800f4f86991620c4d3d90b9bd524999d3b55))



## [0.1.2](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.1...v0.1.2) (2021-03-28)


### Features

* **IR:** add IRBuilder.CreateGEP and IRBuilder.CreateInBoundsGEP ([47f7c92](https://github.com/ApsarasX/llvm-bindings/commit/47f7c9222fabc3ce5bca9296f2acfb313bef42ff))



## [0.1.1](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.0...v0.1.1) (2021-03-28)


### Features

* **IR:** add class PHINode and IRBuilder.CreatePHI ([3cf11fb](https://github.com/ApsarasX/llvm-bindings/commit/3cf11fb766e087bf4ec60aa35c908e847f04340e))
* **IR:** add more create methods of cast instruction in IRBuilder ([14a1a70](https://github.com/ApsarasX/llvm-bindings/commit/14a1a70e8800137c81e4706be5195d36d0e1760d))



## [0.1.0](https://github.com/ApsarasX/llvm-bindings/compare/v0.0.4...v0.1.0) (2021-03-28)


### Features

* **IR:** add class Instruction and supplement several APIs of class BasicBlock ([510973f](https://github.com/ApsarasX/llvm-bindings/commit/510973f2fe56b1960b3a8aa4d94d4db1c99f544e))
* **IR:** add IRBuilder.CreateGlobalString and IRBuilder.CreateGlobalStringPtr ([02bb15c](https://github.com/ApsarasX/llvm-bindings/commit/02bb15ce113bcc30372e3e10c3fedc35dde4bc17))
* **IR:** add several instruction classes, include AllocaInst, BranchInst, CallInst, LoadInst, ReturnInst and StoreInst ([8be97ad](https://github.com/ApsarasX/llvm-bindings/commit/8be97ad42a3c6267a31a19d719cb1d9107c9bc73))
* **IR:** make static 'New' functions of classes with subclasses more precise ([b3bbb66](https://github.com/ApsarasX/llvm-bindings/commit/b3bbb664b6835a9d9becf24bb06dd1ef5e710ddc))


### Performance Improvements

* use HandleScope in right places ([9f6953d](https://github.com/ApsarasX/llvm-bindings/commit/9f6953d83eb387a496335fec7b034c6230e807bb))



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