cmake_minimum_required(VERSION 3.28...4.1)
project(trmfractals VERSION 1.0.0)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

set(src_files
    src/main.cpp
    src/shader.cpp 
    src/canvas2d.cpp
    src/complexscreen.cpp
    src/mandelbrot.cpp
)

add_executable(fractals ${src_files})

target_include_directories(fractals PUBLIC include)

target_link_libraries(fractals PUBLIC glfw)
target_link_libraries(fractals PUBLIC glad)