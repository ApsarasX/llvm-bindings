cmake_minimum_required(VERSION 3.17)

project(llvm-bindings CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CMakeJS)

include(LLVM)

include_directories(${CMAKE_JS_INC} include)

#file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

set(
        SOURCE_FILES
        "src/Util/Inherit.cpp"
        "src/ADT/APInt.cpp"
        "src/ADT/APFloat.cpp"
        "src/ADT/ADT.cpp"
        "src/Bitcode/BitcodeWriter.cpp"
        "src/Bitcode/Bitcode.cpp"
        "src/IR/LLVMContext.cpp"
        "src/IR/Module.cpp"
        "src/IR/Type.cpp"
        "src/IR/IntegerType.cpp"
        "src/IR/PointerType.cpp"
        "src/IR/FunctionType.cpp"
        "src/IR/StructType.cpp"
        "src/IR/ArrayType.cpp"
        "src/IR/Value.cpp"
        "src/IR/User.cpp"
        "src/IR/Constant.cpp"
        "src/IR/ConstantInt.cpp"
        "src/IR/ConstantFP.cpp"
        "src/IR/ConstantPointerNull.cpp"
        "src/IR/GlobalValue.cpp"
        "src/IR/GlobalObject.cpp"
        "src/IR/GlobalVariable.cpp"
        "src/IR/Function.cpp"
        "src/IR/Argument.cpp"
        "src/IR/BasicBlock.cpp"
        "src/IR/DataLayout.cpp"
        "src/IR/IRBuilder.cpp"
        "src/IR/Verifier.cpp"
        "src/IR/IR.cpp"
        "src/Support/Support.cpp"
        "src/Support/Target.cpp"
        "src/Support/TargetRegistry.cpp"
        "src/Target/Target.cpp"
        "src/Target/TargetMachine.cpp"
        "src/llvm-bindings.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${llvm_libs})

execute_process(
        COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
)

string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

add_definitions(-DNAPI_VERSION=7)