cmake_minimum_required(VERSION 3.17)

project(llvm-bindings)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CMakeJS)

include(LLVM)

include_directories(${CMAKE_JS_INC} include)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${CMAKE_JS_SRC} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" LINKER_LANGUAGE CXX)

execute_process(
        COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
)

string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

# Add a library to generate the TypeScript declarations
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/llvm-bindings.d.ts.cpp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/llvm-bindings.in.d.ts ${CMAKE_CURRENT_BINARY_DIR}/llvm-bindings.d.ts.cpp
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/llvm-bindings.in.d.ts
)
add_library(ts_decl_lib OBJECT ${CMAKE_CURRENT_BINARY_DIR}/llvm-bindings.d.ts.cpp)
target_link_libraries(ts_decl_lib ${LLVM_LIBS})
target_compile_options(ts_decl_lib PRIVATE -E -P)
target_include_directories(ts_decl_lib PRIVATE ${LLVM_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} ${NODE_ADDON_API_DIR})

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${LLVM_LIBS})

add_definitions(-DNAPI_VERSION=8)

add_custom_target(
        ts_declarations
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_OBJECTS:ts_decl_lib>" ${CMAKE_CURRENT_SOURCE_DIR}/llvm-bindings.d.ts
        DEPENDS ts_decl_lib
)

add_dependencies(${PROJECT_NAME} ts_declarations)
