include(FindPkgConfig)
# Use a modern CMAKE version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")
file(GLOB FILES ./src/**/*.cpp)
add_library(goon SHARED ${FILES})
target_precompile_headers(goon PRIVATE src/gnpch.hpp)

find_package(spdlog PATH_SUFFIXES .a)
if(NOT spdlog_FOUND)
        message(FATAL "Did you forget to install the submodules?")
endif(NOT spdlog_FOUND)
find_package(glfw3 3.3 REQUIRED PATH_SUFFIXES .a .lib .dll)

# Use newest cpp standard for this target
set_property(TARGET goon PROPERTY CXX_STANDARD 17)
# Define where our compiled FMOD binary files are to be copied from.

#For Debug, print aout all variables.
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_compile_definitions(goon PRIVATE -DGN_BUILD_DLL -DGN_PLATFORM_MACOS -DGN_ENABLE_ASSERTS)
target_compile_options(goon PRIVATE -Wall -Wextra -Wpedantic -Wuninitialized -Wmissing-include-dirs -Wshadow -Wundef -Winvalid-pch)

message(STATUS "Adding include Directories from build submodules, and from header only includes to the project.")
target_link_libraries(goon
        PUBLIC
        spdlog::spdlog
        glfw
        )
target_include_directories(goon
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        spdlog::spdlog
        glfw
        )
message(STATUS "Linking to the external libraries.")
