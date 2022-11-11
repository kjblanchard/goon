cmake_minimum_required(VERSION 3.2)
project(goon_sandbox
        VERSION 0.1.0
        LANGUAGES CXX)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
#This exports a file that clangd can use so that we know what compile/include flags so that we can use clangd language server properly with our cmake attributes.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(goon)
add_subdirectory(sandbox)
