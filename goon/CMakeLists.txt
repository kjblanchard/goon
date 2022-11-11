include(FindPkgConfig)
# Use a modern CMAKE version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")
file(GLOB FILES ./src/**/*.cpp)
add_library(goon SHARED ${FILES})

find_package(spdlog PATH_SUFFIXES .a)
if(NOT spdlog_FOUND)
        #Build submodules
        #For some reason, these are much larger, but will not worry about it for now.
        add_subdirectory(vendor/spdlog)
endif(NOT spdlog_FOUND)

# Use newest cpp standard for this target
set_property(TARGET goon PROPERTY CXX_STANDARD 17)
# Define where our compiled FMOD binary files are to be copied from.

#For Debug, print aout all variables.
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

target_compile_definitions(goon PRIVATE -DGN_BUILD_DLL -DGN_PLATFORM_MACOS )
target_compile_options(goon PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors
-Wno-global-constructors -Wno-constant-conversion  -Wno-sign-conversion -Wno-float-conversion -Wno-double-promotion)

message(STATUS "Adding include Directories from build submodules, and from header only includes to the project.")
target_link_libraries(goon
        PUBLIC
        spdlog::spdlog
        )
target_include_directories(goon
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        spdlog::spdlog
        )
message(STATUS "Linking to the external libraries.")
