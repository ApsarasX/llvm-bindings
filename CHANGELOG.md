## [0.2.3](https://github.com/ApsarasX/llvm-bindings/compare/v0.2.2...v0.2.3) (2021-10-29)


### Bug Fixes

* **IR:** add missing signature of IRBuilder.CreateResume ([a1271cb](https://github.com/ApsarasX/llvm-bindings/commit/a1271cb9d29ec6ee89f46894cf5831a945b8e3dd))
* **IR:** address transmission of InsertPoint's temporary object ([a07a1fe](https://github.com/ApsarasX/llvm-bindings/commit/a07a1fe958db52443a26769ed6505e282fb3efbd))
* **IR:** IRBuilder.SetInsertPoint typo ([e2db57d](https://github.com/ApsarasX/llvm-bindings/commit/e2db57d44661288804582a7d3e5fe1eb451fecc1))


### Features

* **IR:** add class ConstantExpr ([fbe662f](https://github.com/ApsarasX/llvm-bindings/commit/fbe662fba4cc269a02c62916dc9b92f309f4f24f))
* **IR:** add ConstantExpr.getType ([fb751eb](https://github.com/ApsarasX/llvm-bindings/commit/fb751eba4d0f989317c8372d85620497e343a1ed))
* **IR:** add DataLayout.getTypeAllocSize ([18044f0](https://github.com/ApsarasX/llvm-bindings/commit/18044f0beb96fee08b00ad0d50fa3a21d69a8675))
* **IR:** add Function.hasPersonalityFn, Function.setPersonalityFn and Function.setDoesNotThrow ([6238bf6](https://github.com/ApsarasX/llvm-bindings/commit/6238bf60d88ac84cf1acae225f92df1f99819ef6))
* **IR:** add Function.insertInto, Function.removeFromParent and Function.eraseFromParent ([43fda5c](https://github.com/ApsarasX/llvm-bindings/commit/43fda5c81b0221666782f781b16362d553bb1c1f))
* **IR:** add Intrinsic ([403f747](https://github.com/ApsarasX/llvm-bindings/commit/403f74740cc4023965a96041d8734e278c9d0865))
* **IR:** add InvokeInst and IRBuilder.CreateInvoke ([520f7a3](https://github.com/ApsarasX/llvm-bindings/commit/520f7a3f0256727e46b16b7f9f7ac1f4677b43d3))
* **IR:** add IRBuilder.CreateInsertValue ([6f60ded](https://github.com/ApsarasX/llvm-bindings/commit/6f60ded1d1b1222704949cc4903343b9aae60ebc))
* **IR:** add IRBuilder.InsertPoint, IRBuilder.saveIP, IRBuilder.saveAndClearIP and IRBuilder.restoreIP ([4303af6](https://github.com/ApsarasX/llvm-bindings/commit/4303af691306121ffdceec7ea136ce92b97b1563))
* **IR:** add LandingPadInst, IRBuilder.CreateExtractValue and IRBuilder.CreateLandingPad ([2bd479a](https://github.com/ApsarasX/llvm-bindings/commit/2bd479aa71d22b5cfd7dba539776b25a1aed9e0c))
* **IR:** add Module.getOrInsertFunction and FunctionCallee ([693fdd5](https://github.com/ApsarasX/llvm-bindings/commit/693fdd598a25fdcbaf8360f88de7d0cb8ee39c39))
* **IR:** add overloaded form of IRBuilder.CreateCall ([1909cb8](https://github.com/ApsarasX/llvm-bindings/commit/1909cb869b1f4edfad91071a97af41be585ab5d6))
* **IR:** add overloaded form of IRBuilder.CreateCall ([d150d2c](https://github.com/ApsarasX/llvm-bindings/commit/d150d2cbad3f62a3915d584c63a304bd929011ad))
* **IR:** add overloaded form of IRBuilder.CreateInvoke ([815122d](https://github.com/ApsarasX/llvm-bindings/commit/815122dbae3c2210fac7bc557b492751d91a29ba))
* **IR:** add ResumeInst and IRBuilder.CreateResume ([95358ad](https://github.com/ApsarasX/llvm-bindings/commit/95358ade3ee25e48be2e30cf533e18d05e3e7e75))
* **IR:** add some duplicated methods of Type and Type.isSameType ([0d6eabc](https://github.com/ApsarasX/llvm-bindings/commit/0d6eabcbe6272f4439571c7294715f6ff4192e8e))
* **IR:** add StructType.get ([7e27eee](https://github.com/ApsarasX/llvm-bindings/commit/7e27eeec1f05f820f2fb2d87c3145b2bf4b40e1d))



## [0.2.2](https://github.com/ApsarasX/llvm-bindings/compare/v0.2.1...v0.2.2) (2021-10-15)


### Features

* **IR:** add ConstantFP.getType ([7c788b4](https://github.com/ApsarasX/llvm-bindings/commit/7c788b4157fa65ae69106d74b53ae188d3f473ef))
* **IR:** add ConstantFP.getType ([8106c4e](https://github.com/ApsarasX/llvm-bindings/commit/8106c4ef07fdd3aebe99a8f3acba9e02b704aa99))
* **IR:** add Function.deleteBody, Function.removeFromParent and Function.eraseFromParent ([e7ad3bf](https://github.com/ApsarasX/llvm-bindings/commit/e7ad3bfc31a19df86dcf8f561309d9fe3933a187))
* **IR:** add Function.getNumUses and Function.removeDeadConstantUsers ([a770a28](https://github.com/ApsarasX/llvm-bindings/commit/a770a2823606affa42b3d03a758d5b7a5dffa893))
* **IR:** add GlobalVariable.removeFromParent and GlobalVariable.eraseFromParent ([b625e09](https://github.com/ApsarasX/llvm-bindings/commit/b625e09c631b3a4d81836c9f2f9f4db5b560e1ce))
* **IR:** add IntegerType.isIntegerTy ([3effe47](https://github.com/ApsarasX/llvm-bindings/commit/3effe4763c26faf6ddb9705861f0be10f5d10919))
* **IR:** add IRBuilder.CreateUnreachable ([9d91aa6](https://github.com/ApsarasX/llvm-bindings/commit/9d91aa6234cb3bb810fdad740b85c705c2302aa7))
* **IR:** add PointerType.isIntegerTy ([75edd4f](https://github.com/ApsarasX/llvm-bindings/commit/75edd4f9151ec48b683b8aeff2c81186998b9ef8))
* **IR:** add StructType.isIntegerTy ([086e647](https://github.com/ApsarasX/llvm-bindings/commit/086e647cb1b4e105259e2caa31063491fcf45ed9))
* **IR:** add SwitchInst ([042c942](https://github.com/ApsarasX/llvm-bindings/commit/042c942f5111933d35d4539a2c215d098e9f2249))
* **IR:** add UnreachableInst ([ec9666a](https://github.com/ApsarasX/llvm-bindings/commit/ec9666acc309264e9a674890a990d7656ebe8a8a))
* **IR:** add Value.user_empty, Function.use_empty and Function.user_empty ([34ccfd7](https://github.com/ApsarasX/llvm-bindings/commit/34ccfd73e84c30f71b9871e3a691c05082722910))
* **Linker:** add Linker ([71437ba](https://github.com/ApsarasX/llvm-bindings/commit/71437ba9242da3eca697863af4d824717d89ecd1))



## [0.2.1](https://github.com/ApsarasX/llvm-bindings/compare/v0.2.0...v0.2.1) (2021-09-29)


### Bug Fixes

* **IR:** update the parameter list format when using llvm::Function::Create ([5f0802f](https://github.com/ApsarasX/llvm-bindings/commit/5f0802fdd8a3083fc495005a2f06813388d11793))



# [0.2.0](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.8...v0.2.0) (2021-05-24)


### Features

* switch the version of llvm to 12 ([ff505cc](https://github.com/ApsarasX/llvm-bindings/commit/ff505cc9d6a3f18d63fbbc628f28b05a7cedb2b6))



## [0.1.8](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.7...v0.1.8) (2021-05-24)


### Bug Fixes

* allow undefined or null for middle arguments of BasicBlock.Create and close [#5](https://github.com/ApsarasX/llvm-bindings/issues/5) ([84bf31f](https://github.com/ApsarasX/llvm-bindings/commit/84bf31f0564e43a7cae7e963d6a19f3f57c73d23))
* error message typo ([4f5a356](https://github.com/ApsarasX/llvm-bindings/commit/4f5a3561d864957b5e1f53c146f606c3a8a91788))
* prevent phi node addIncoming from always throwing and close [#4](https://github.com/ApsarasX/llvm-bindings/issues/4) ([9068055](https://github.com/ApsarasX/llvm-bindings/commit/9068055105acc1693b0e7f4a50b7fff4c5f78b09))


### Features

* add several duplicated method for [#1](https://github.com/ApsarasX/llvm-bindings/issues/1) ([5af02bc](https://github.com/ApsarasX/llvm-bindings/commit/5af02bc38f2af107ee19ab601d3d0445174e0b7f))
* **IR:** add some duplicated methods due to missing inheritance of node-api ([8da2f66](https://github.com/ApsarasX/llvm-bindings/commit/8da2f661073ce2260ea2e6b0596229a938154843))



## [0.1.7](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.6...v0.1.7) (2021-04-20)


### Bug Fixes

* **IR:** fix the problem about verification of ConstantPointerNull.get ([f1fcd6f](https://github.com/ApsarasX/llvm-bindings/commit/f1fcd6f967c766209c0ec00468131f4d24b3c41f))


### Features

* **IR:** add some unary operations of IRBuilder ([85361c6](https://github.com/ApsarasX/llvm-bindings/commit/85361c6bfac36cf476c174e651b9a5aa9e3a9bc3))



## [0.1.6](https://github.com/ApsarasX/llvm-bindings/compare/v0.1.5...v0.1.6) (2021-04-13)


### Bug Fixes

* **IR:** change the return type of IRBuilder.Create<Inst> to the corresponding instruction type ([45be7ed](https://github.com/ApsarasX/llvm-bindings/commit/45be7ed768ae094dbced767355a65240f4c229aa))


### Features

* **IR:** add Argument.setName ([671a70f](https://github.com/ApsarasX/llvm-bindings/commit/671a70f5532417a2c390919b8fb1fcba119e096c))
* **IR:** add class ConstantStruct ([c1033c6](https://github.com/ApsarasX/llvm-bindings/commit/c1033c6d157b9b9b976e6618ccdb85f60107a064))
* **IR:** add Function.getExitBlock ([93b55fb](https://github.com/ApsarasX/llvm-bindings/commit/93b55fb571f7c28d18585541e603b84447dceaee))
* **IR:** add PointerType.getUnqual ([3c4ccbc](https://github.com/ApsarasX/llvm-bindings/commit/3c4ccbc0c6bb8d2ec618d2fe8da23d25b85bf3c3))
* **IR:** add StructType.create and StructType.setBody ([b814313](https://github.com/ApsarasX/llvm-bindings/commit/b814313b1209a51842af779927e4fbb52166d24b))



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