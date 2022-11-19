include(FindPkgConfig)
cmake_minimum_required(VERSION 3.16)
message(STATUS "Starting Goon Engine configuration")
file(GLOB_RECURSE GOONFILES src/*.c* src/*.h*)
#Platform specific Project setup
if(APPLE)
        file(GLOB_RECURSE OBJCFILES src/*.mm)
        list(APPEND GOONFILES ${OBJCFILES})
        if(NOT IOS)
                set(CMAKE_THREAD_LIBS_INIT "-lpthread") #We need to say that we have threads, or else borked for some reason.
                set(CMAKE_HAVE_THREADS_LIBRARY 1)
                set(CMAKE_USE_WIN32_THREADS_INIT 0)
                set(CMAKE_USE_PTHREADS_INIT 1)
                set(THREADS_PREFER_PTHREAD_FLAG ON)
        endif(NOT IOS)
endif(APPLE)
add_library(goon SHARED ${GOONFILES})

message(STATUS "Finding libraries")
#Preinstalled libraries
find_package(spdlog PATH_SUFFIXES .a .lib .dll REQUIRED)
find_package(glfw3 3.3 REQUIRED PATH_SUFFIXES .a .lib .dll)
#Libraries to build.
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

message(STATUS "Setting flags")
set_property(TARGET goon PROPERTY CXX_STANDARD 17)

#For Debug, print aout all variables.
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

message(STATUS "Setting up PCH, mac needs objc")
if(APPLE)
target_precompile_headers(goon PRIVATE
    "$<$<COMPILE_LANGUAGE:OBJCXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/gnpch.hpp>")
else()
target_precompile_headers(goon PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/gnpch.hpp>")
endif(APPLE)

target_compile_definitions(goon PRIVATE 
        -DGN_BUILD_DLL -DGN_PLATFORM_MACOS -DGN_ENABLE_ASSERTS #Engine defines that we use, probably set these as CMAKE things
        -DGL_SILENCE_DEPRECATION -DGLFW_INCLUDE_NONE 
        -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM #Used since we use glad
        )
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
