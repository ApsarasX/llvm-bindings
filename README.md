# llvm-bindings

LLVM bindings for Node.js/JavaScript/TypeScript

[![github-action](https://img.shields.io/github/workflow/status/ApsarasX/llvm-bindings/Build?style=flat-square)](https://github.com/ApsarasX/llvm-bindings/actions)
[![npm](https://img.shields.io/npm/v/llvm-bindings?style=flat-square)](https://www.npmjs.com/package/llvm-bindings)
[![github-license](https://img.shields.io/github/license/ApsarasX/llvm-bindings?style=flat-square)](https://github.com/ApsarasX/llvm-bindings/blob/master/LICENSE)

## Supported OS

|  | x86_64 | ARM64 |
| :---: | :---: | :---: |
| macOS 10.15 Catalina | ✅ | / |
| macOS 11 Big Sur | ✅ | ✅ |
| macOS 12 Monterey | ✅ | ✅ |
| Ubuntu 18.04 | ✅ | ✅ |
| Ubuntu 20.04 | ✅ | ✅ |
| Ubuntu 21.10 | ✅ | ✅ |
| Windows 10 | ✅ | ⚠️ |
| Windows 11 | ⚠️ | ⚠️ |

> ⚠️ means not tested.

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
sudo ./llvm.sh 13

# install cmake and zlib by apt-get
sudo apt-get install cmake zlib1g-dev

# install llvm-bindings by npm
npm install llvm-bindings
```

### Install on Windows

First, please refer to [Build LLVM from sources on Windows 10](https://github.com/ApsarasX/llvm-bindings/wiki/Build-LLVM-from-source-code-on-Windows-10) to build LLVM.

Then, find the `llvm-config` command in your LLVM build directory and execute `llvm-config --cmakedir` to get LLVM cmake directory, assuming `C:\Users\dev\llvm-13.0.1.src\build\lib\cmake\llvm`.

Finally, execute the following commands.

```shell
# specify the LLVM cmake directory for cmake-js
npm config set cmake_LLVM_DIR C:\Users\dev\llvm-13.0.1.src\build\lib\cmake\llvm

# install llvm-bindings by npm
npm install llvm-bindings
```

> You can also install `llvm-bindings` in WSL2 if your OS is Windows.

### Custom LLVM Installation
You can use the npm configuration options to set the path to the LLVM cmake directory. This is needed if you don't want to use the system default LLVM installation.

```shell
# specify the llvm cmake directory by npm and cmake-js
npm config set cmake_LLVM_DIR $(path-to-llvm/bin/llvm-config --cmakedir)

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
    builder.SetInsertPoint(entryBB);
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
    console.log(module.print());
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
|  0.3.x        |  13.0.x         |

## Acknowledgments
- [MichaReiser](https://github.com/MichaReiser): the creator of [llvm-node](https://github.com/MichaReiser/llvm-node)

> [llvm-bindings](https://github.com/ApsarasX/llvm-bindings) is mostly inspired by [llvm-node](https://github.com/MichaReiser/llvm-node).
