project(glad
    VERSION 1.0.0
    LANGUAGES C)
file(GLOB FILES src/glad.c)
add_library(glad ${FILES})
target_include_directories(glad
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )
set(GLAD_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/glfw3")
