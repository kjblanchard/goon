include(FindPkgConfig)
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Goon Engine configuration")
file(GLOB GOONFILES src/**/*.cpp)
add_library(goon SHARED ${GOONFILES})
target_precompile_headers(goon PRIVATE src/gnpch.hpp)

find_package(spdlog PATH_SUFFIXES .a .lib .dll REQUIRED)
find_package(glfw3 3.3 REQUIRED PATH_SUFFIXES .a .lib .dll)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
set_property(TARGET goon PROPERTY CXX_STANDARD 17)

#For Debug, print aout all variables.
get_cmake_property(_variableNames VARIABLES)

#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_compile_definitions(goon PRIVATE 
        -DGN_BUILD_DLL -DGN_PLATFORM_MACOS -DGN_ENABLE_ASSERTS
        -DGL_SILENCE_DEPRECATION -DGLFW_INCLUDE_NONE)
target_compile_options(goon PRIVATE -Wall -Wextra -Wpedantic -Wdeprecated -Wextra-semi )

target_link_libraries(goon
        PUBLIC
        spdlog::spdlog
        glfw
        glad
        imgui
        )
target_include_directories(goon
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        spdlog::spdlog
        glfw
        "${CMAKE_SOURCE_DIR}/vendor/glad"
        vendor/glad/include/
        vendor/imgui
        )
