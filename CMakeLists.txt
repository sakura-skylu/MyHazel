cmake_minimum_required(VERSION 3.20)
project(MyHazel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Vendor/spdlog)
add_subdirectory(Vendor/glfwm)

add_subdirectory(Engine)
add_subdirectory(Editor)
