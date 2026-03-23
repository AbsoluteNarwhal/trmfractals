# Fractals!

This is code for an essay submitted for the Tom Rocks Maths / Oxford University [essay competition](https://tomrocksmaths.com/trm-essay-competition/). Written in C++, it uses OpenGL to render fractals such as the Mandelbrot Set using only a fragment shader.

## Build Instructions

1. Ensure you have the following:

    - C++ Compiler (Clang, MSVC, GCC, etc.). Only Clang is tested but others should work.
    - CMake
    - Build system (Visual Studio, Make, Ninja, etc.)
    - 64-bit Windows or 64-bit Linux operating system
    - OpenGL 3.3 compatible graphics card and operating system

2. Clone the repository: `git clone https://github.com/absolutenarwhal/trmfractals`, `cd trmfractals`

3. Install dependencies: `git submodule update --init --recursive`

4. Build project with CMake: `cd build`, `cmake ..`, `cmake --build .`

5. Run project: `./out/fractals`