include(FindPkgConfig)
# Use a modern CMAKE version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")
file(GLOB FILES ./src/**/*.cpp)
add_library(goon SHARED ${FILES})
# Use newest cpp standard for this target
set_property(TARGET goon PROPERTY CXX_STANDARD 17)
# Define where our compiled FMOD binary files are to be copied from.

target_compile_options(goon PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors
-Wno-global-constructors -Wno-constant-conversion  -Wno-sign-conversion -Wno-float-conversion -Wno-double-promotion)

message(STATUS "Adding include Directories from build submodules, and from header only includes to the project.")
target_include_directories(goon
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        )
message(STATUS "Linking to the external libraries.")
