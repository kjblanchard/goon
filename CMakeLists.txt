# 3.16 for pch support
cmake_minimum_required(VERSION 3.16)
project(goon_sandbox
        VERSION 0.1.0
        LANGUAGES CXX)

if(APPLE)
        enable_language(OBJC)
endif(APPLE)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(GOON_ENABLE_TESTING "Enables the tests to be created" ON)

if(GOON_ENABLE_TESTING)
        enable_testing()
endif(GOON_ENABLE_TESTING)
enable_testing()

# This exports a file that clangd can use so that we know what compile/include flags so that we can use clangd language server properly with our cmake attributes.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(goon)
add_subdirectory(sandbox)
