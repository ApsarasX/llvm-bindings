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
brew install cmake llvm

# install llvm-bindings by npm
npm install llvm-bindings
```

### Install on Ubuntu

```shell
#install llvm by installation script
wget https://apt.llvm.org/llvm.sh
sudo chmod +x llvm.sh
sudo ./llvm.sh

# install cmake by apt-get
sudo apt-get install cmake

# install llvm-bindings by npm
npm install llvm-bindings
```

## Usage

```javascript
import llvm from 'llvm-bindings';

function main(): void {
    const context = new llvm.LLVMContext();
    const module = new llvm.Module('demo', context);
    const builder = new llvm.IRBuilder(context);

    const returnType = builder.getInt32Ty();
    const paramTypes = [builder.getInt32Ty(), builder.getInt32Ty()];
    const functionType = llvm.FunctionType.get(returnType, paramTypes, false);
    const func = llvm.Function.Create(functionType, llvm.Function.LinkageTypes.ExternalLinkage, 'add', module);

    const entryBB = llvm.BasicBlock.Create(context, 'entry', func);
    builder.SetInsertionPoint(entryBB);
    const a = func.getArg(0);
    const b = func.getArg(1);
    const result = builder.CreateAdd(a, b);
    builder.CreateRet(result);

    if (llvm.verifyFunction(func)) {
        console.error('Verifying function failed');
        return;
    }
    if (llvm.verifyModule(module)) {
        console.error('Verifying module failed');
        return;
    }
    module.print();
}

main();
```

> You cannot declare a variable or constant named `module` in top level, because `module` is a built-in object in Node.js.

## Note
Due to the limitation of `node-addon-api`, this project has not implemented inheritance yet, so calling the method of superclass from subclass object will report an error. Please see [#1](https://github.com/ApsarasX/llvm-bindings/issues/1) for details.

## Compatibility

| llvm-bindings versions  |  compatible LLVM versions |
| ------------ | ------------ |
|  0.0.x, 0.1.x |  11.0.x, 11.1.x |
|  0.2.x        |  12.0.x         |

## Acknowledgments
- [MichaReiser](https://github.com/MichaReiser): the creator of [llvm-node](https://github.com/MichaReiser/llvm-node)

> [llvm-bindings](https://github.com/ApsarasX/llvm-bindings) is mostly inspired by [llvm-node](https://github.com/MichaReiser/llvm-node).
