# llvm-bindings

LLVM bindings for Node.js/JavaScript/TypeScript

## Supported OS

- [x] macOS
- [x] Ubuntu
- [ ] Windows

## Supported LLVM methods

listed in the [TypeScript definition file](./llvm-bindings.d.ts).

## Install

### Install on macOS

```shell
# install cmake and llvm by homebrew
brew install cmake llvm@11

# install llvm-bindings
npm install llvm-bindings
```

### Install on Ubuntu

```shell
# install cmake and llvm by apt-get
sudo apt-get install cmake llvm-11

# install llvm-bindings
npm install llvm-bindings
```

## Usage

```javascript
// If you have configured ES module or TypeScript, you can replace the next line with `import llvm from 'llvm-bindings';`
const llvm = require('llvm-bindings');

const context = new llvm.LLVMContext();
const mod = new llvm.Module('demo', context);
const builder = new llvm.IRBuilder(context);

const returnType = builder.getInt32Ty();
const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'add', mod);

const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
builder.SetInsertionPoint(entryBB);

const a = func.getArg(0);
const b = func.getArg(1);
const result = builder.CreateAdd(a, b);
builder.CreateRet(result);

if (!llvm.verifyFunction(func) && !llvm.verifyModule(mod)) {
    mod.print();
}
```

> Note: You cannot declare a variable or constant named `module` in top level, because `module` is a built-in object in Node.js.

## Compatibility

| llvm-bindings versions  |  compatible LLVM versions |
| ------------ | ------------ |
|  0.0.x, 0.1.x |  11.0.x, 11.1.x |

## Acknowledgments
- [MichaReiser](https://github.com/MichaReiser): the creator of [llvm-node](https://github.com/MichaReiser/llvm-node)

> [llvm-bindings](https://github.com/ApsarasX/llvm-bindings) is mostly inspired by [llvm-node](https://github.com/MichaReiser/llvm-node).
