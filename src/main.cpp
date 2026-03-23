#include "canvas2d.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <memory>

// Uniforms (mandelbrot parameters)
float centerX = -0.5;
float centerY = 0.0;
float zoom = 0.65;
int maxIter = 256;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas) {
    if (!canvas.get()->getShaderProgram()->getProgram().has_value()) return;
    unsigned int prog = canvas.get()->getShaderProgram()->getProgram().value();

    glUniform2f(glGetUniformLocation(prog, "u_center"), centerX, centerY);
    glUniform1f(glGetUniformLocation(prog, "u_zoom"), zoom);
    glUniform1i(glGetUniformLocation(prog, "u_maxIter"), maxIter);
}

int main(int argc, char** argv) {
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

    std::shared_ptr<Canvas2D> canvas = std::make_shared<Canvas2D>("../shaders/mandelbrot.frag", mandelbrotRenderCallback);
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