#include "canvas2d.h"
#include "mandelbrot.h"
#include "complexscreen.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <memory>

enum class FractalType {
    MandelbrotSet
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    FractalType fractalType;

    // Get fractal type
    if (argc == 1) {
        fractalType = FractalType::MandelbrotSet;
    }
    else if (argc > 2) {
        std::cout << "Error: too many arguments" << std::endl;
        return -1;
    }
    else if (strcmp(argv[1], "mandelbrot") == 0) {
        fractalType = FractalType::MandelbrotSet;
    }
    else {
        std::cout << "Error: unknown fractal type: '" << argv[1] << "'" << std::endl;
        return -1;
    }

    if (!glfwInit()){
        std::cout << "Error: could not initialise GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Fractals", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error: could not create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: could not initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    std::shared_ptr<Canvas2D> canvas;

    switch (fractalType) {
        case FractalType::MandelbrotSet:
            canvas = std::make_shared<Canvas2D>("../shaders/mandelbrot.frag", mandelbrotRenderCallback);
    }

    if (!canvas->initSuccessful) {
        std::cout << "Error: could not initialize canvas2D" << std::endl;
        return -1;
    }

    // Main loop
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        canvas->loop();

        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}