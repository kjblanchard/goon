file(GLOB FILES src/**/*.cpp)
file(GLOB MAIN ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(APPEND FILES ${MAIN})
add_executable(sandbox
                ${FILES})
set_property(TARGET sandbox PROPERTY CXX_STANDARD 17)
target_compile_definitions(sandbox PRIVATE -DGN_PLATFORM_MACOS )
target_include_directories(sandbox
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "./goon/src"
        )
target_link_libraries(sandbox PUBLIC goon)
target_compile_options(sandbox PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
# Set relative link for this lib.
set_target_properties(sandbox
    PROPERTIES LINK_FLAGS "-Wl,-rpath,../lib")
