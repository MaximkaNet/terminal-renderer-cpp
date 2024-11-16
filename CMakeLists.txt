cmake_minimum_required(VERSION 3.22)

project(renderer LANGUAGES CXX)

# static link
# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# C++17 needed for imgui
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


add_subdirectory(src)
add_subdirectory(test)