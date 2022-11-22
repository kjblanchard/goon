cmake_minimum_required(VERSION 3.16)
message(STATUS "Starting Goon Engine configuration")

# #########################################
# File globbing
# #########################################
message(STATUS "Getting all files for cmake..")
file(GLOB_RECURSE GOONFILES src/*.c* src/*.h*)

# #########################################
# Platform specific Project setup
# #########################################
message(STATUS "Changing the platform specific settings")
if(APPLE)
        file(GLOB_RECURSE OBJCFILES src/*.mm)
        list(APPEND GOONFILES ${OBJCFILES})

        # MACOS
        if(NOT IOS)
                set(CMAKE_THREAD_LIBS_INIT "-lpthread") # We need to say that we have threads, or else borked for some reason.
                set(CMAKE_HAVE_THREADS_LIBRARY 1)
                set(CMAKE_USE_WIN32_THREADS_INIT 0)
                set(CMAKE_USE_PTHREADS_INIT 1)
                set(THREADS_PREFER_PTHREAD_FLAG ON)
        endif(NOT IOS)
endif(APPLE)

if(WIN32)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /c/cmake)
endif(WIN32)

# #########################################
# Initialize
# #########################################
message(STATUS "Initializing the project")
include(FindPkgConfig)
add_library(goon STATIC ${GOONFILES})
set_property(TARGET goon PROPERTY CXX_STANDARD 20)
if(UNIX AND NOT APPLE)
        set(LINUX ON)
endif(UNIX AND NOT APPLE)

# #########################################
# Options
# #########################################
option(GOON_BUILD_PCH "Uses a PCH file to try and speed up compilation" ON)
option(GOON_BUILD_ENGINE "Builds the full engine into the project" ON)
option(CMAKE_DEBUG_VARIABLES "Runs a debug on all variables for troubleshooting" OFF)

# #########################################
# Build libraries
# #########################################
message(STATUS "Building libraries")

# GLAD
add_subdirectory(vendor/glad)

# IMGUI
add_subdirectory(vendor/imgui)

# spdlog
add_subdirectory(vendor/spdlog)

# glfw
set(ENKITS_BUILD_EXAMPLES OFF CACHE BOOL "Build basic example applications")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(vendor/glfw)

# #########################################
# For Debug, print aout all variables.
# #########################################
if(CMAKE_DEBUG_VARIABLES)
        message(STATUS "Exporting debug")
        get_cmake_property(_variableNames VARIABLES)
        list(SORT _variableNames)

        foreach(_variableName ${_variableNames})
                message(STATUS "${_variableName}=${${_variableName}}")
        endforeach()
endif(CMAKE_DEBUG_VARIABLES)

# #########################################
# Precompiled headers
# #########################################
if(GOON_BUILD_PCH)
        message(STATUS "Setting up PCH, mac needs objc")

        if(APPLE)
                target_precompile_headers(goon PRIVATE
                        "$<$<COMPILE_LANGUAGE:OBJCXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/gnpch.hpp>")
        else()
                target_precompile_headers(goon PRIVATE
                        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/gnpch.hpp>")
        endif(APPLE)
endif(GOON_BUILD_PCH)

# #########################################
# Compile Definitions
# #########################################
target_compile_definitions(goon PRIVATE
        -DGL_SILENCE_DEPRECATION
        -DIMGUI_IMPL_OPENGL_LOADER_GLAD # Used since we use glad?
)

if(GOON_BUILD_ENGINE)
        target_compile_definitions(goon PRIVATE
                -DGN_BUILD_DLL # Builds the full project
                -DGN_ENABLE_ASSERTS # Enables asserts
        )
endif(GOON_BUILD_ENGINE)

if(APPLE)
        target_compile_definitions(goon PRIVATE -DGN_PLATFORM_MACOS)
elseif(WIN32)
        target_compile_definitions(goon PRIVATE -DGN_PLATFORM_WINDOWS)
elseif(LINUX)
        target_compile_definitions(goon PRIVATE -DGN_PLATFORM_LINUX)
endif(APPLE)

# #########################################
# Compile Options
# #########################################
target_compile_options(goon PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wdeprecated
        -Wextra-semi
)

# #########################################
# Linking Option
# #########################################
target_link_libraries(goon
        PUBLIC
        spdlog::spdlog

        PRIVATE
        glfw
        glad
        imgui
)

target_include_directories(goon
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"

        PRIVATE
        spdlog::spdlog
        glfw
        "${CMAKE_SOURCE_DIR}/vendor/glad"
        vendor/glad/include/
        vendor/imgui
        vendor/glm/
)
