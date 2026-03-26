# Fractals!

This is code for an essay submitted for the [Tom Rocks Maths / Oxford University essay competition](https://tomrocksmaths.com/trm-essay-competition/). Written in C++, it uses OpenGL to render fractals such as the Mandelbrot Set while utilising the GPU as much as possible.

## Usage Instructions

Builds are only provided for Windows. If you're on another platform, you'll have to build from source (see build instructions).

1. Download the latest version from the releases tab.

2. Unzip the folder and run `fractals.exe`. This will open the Mandelbrot Set renderer.

### Controls

- Scroll or pinch touchpad to zoom into the fractal. Click and drag to pan.

- Press 'H' to toggle the settings panel.

- Max. iterations: Number of iterations the program computes. Increasing this will make the render more accurate at the cost of performance.

- Draw divergent colours: When enabled, colours values not in the set based on how fast they diverge. Disable this to colour everything white.

- Colour frequency: Controls how fast the colours of divergent values change.

## Build Instructions

1. Ensure you have the following:

    - C++ Compiler (Clang, MSVC, GCC, etc.). Only Clang is tested but others should work.
    - CMake
    - Build system (Visual Studio, Make, Ninja, etc.)
    - OpenGL 3.3 compatible graphics card and operating system

2. Clone the repository: `git clone https://github.com/absolutenarwhal/trmfractals`, `cd trmfractals`

3. Install dependencies: `git submodule update --init --recursive`

4. Build project with CMake: `cd build`, `cmake ..`, `cmake --build .`

5. Run project: `cd out`, `./fractals`