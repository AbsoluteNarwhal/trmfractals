cmake_minimum_required(VERSION 3.28...4.3)

project(trmfractals VERSION 0.1.0)

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

    # imgui
    extern/imgui/imgui.cpp 
    extern/imgui/imgui_demo.cpp 
    extern/imgui/imgui_draw.cpp 
    extern/imgui/imgui_tables.cpp 
    extern/imgui/imgui_widgets.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp 
    extern/imgui/backends/imgui_impl_opengl3.cpp
    extern/imgui/misc/cpp/imgui_stdlib.cpp
)

add_executable(fractals ${src_files})

target_include_directories(fractals PUBLIC include)
target_include_directories(fractals PUBLIC extern/imgui)
target_include_directories(fractals PUBLIC extern/imgui/backends)
target_include_directories(fractals PUBLIC extern/imgui/misc/cpp)

target_compile_definitions(fractals PUBLIC TRMFRACTALS_VERSION="0.1.0-alpha")

target_link_libraries(fractals PUBLIC glfw)
target_link_libraries(fractals PUBLIC glad)

add_custom_command(
    TARGET fractals POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "${CMAKE_BINARY_DIR}/out/resources/shaders"
)