file(GLOB FILES src/**/*.cpp)
file(GLOB MAIN ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(APPEND FILES ${MAIN})
add_executable(sandbox
        ${FILES})
set_property(TARGET sandbox PROPERTY CXX_STANDARD 20)

if(WIN32)
        target_compile_definitions(sandbox PRIVATE
                -DGN_PLATFORM_WINDOWS
                -DGN_ENABLE_ASSERTS # Engine defines that we use, probably set these as CMAKE things
        )
elseif(APPLE)
        target_compile_definitions(sandbox PRIVATE
                -DGN_PLATFORM_MACOS
                -DGN_ENABLE_ASSERTS # Engine defines that we use, probably set these as CMAKE things
        )
else()
        target_compile_definitions(sandbox PRIVATE
                -DGN_PLATFORM_LINUX
                -DGN_ENABLE_ASSERTS # Engine defines that we use, probably set these as CMAKE things
        )
endif(WIN32)

target_include_directories(sandbox
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "./goon/src"
)
target_link_libraries(sandbox PUBLIC goon)
target_compile_options(sandbox PRIVATE -Wall -Wextra -Wpedantic -Wdeprecated -Wextra-semi)

# Set relative link for this lib.
set_target_properties(sandbox
        PROPERTIES LINK_FLAGS "-Wl,-rpath,../lib")
