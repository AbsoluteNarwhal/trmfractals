#include "mandelbrot.h"
#include "canvas2d.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

// Mandelbrot parameters (uniforms)
float centerX = -0.5;
float centerY = 0.0;
float zoom = 0.35;
int maxIter = 256;

void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas) {
    if (!canvas.get()->getShaderProgram()->getProgram().has_value()) return;
    unsigned int prog = canvas.get()->getShaderProgram()->getProgram().value();

    glUniform2f(glGetUniformLocation(prog, "u_center"), centerX, centerY);
    glUniform1f(glGetUniformLocation(prog, "u_zoom"), zoom);
    glUniform1i(glGetUniformLocation(prog, "u_maxIter"), maxIter);
}

void screenToComplex(GLFWwindow* w, double px, double py, float& re, float& im) {
    int W, H;
    glfwGetFramebufferSize(w, &W, &H);
    float ndcX = -((float)(px / W) * 2.0f - 1.0f);
    float ndcY = (float)(py / H) * 2.0f - 1.0f;
    re = ndcX / zoom + centerX;
    im = ndcY / zoom + centerY;
}

void zoomToward(float re, float im, float factor) {
    centerX = re + (centerX - re) * factor;
    centerY = im + (centerY - im) * factor;
    zoom *= factor;
}