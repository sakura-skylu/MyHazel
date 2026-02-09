add_library(Engine STATIC
    src/Engine.cpp
    src/Log.cpp
    src/Application.cpp
    src/Window.cpp
)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Engine PUBLIC
    spdlog::spdlog
    glfw
)

# Windows下需要这个宏，避免 GLFW 头文件包含 windows.h 乱七八糟
target_compile_definitions(Engine PRIVATE GLFW_INCLUDE_NONE)
