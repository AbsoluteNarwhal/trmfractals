#include "canvas2d.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <memory>

// Mandelbrot parameters (uniforms)
float centerX = -0.5;
float centerY = 0.0;
float zoom = 0.35;
int maxIter = 256;

// Dragging (touchpad)
bool dragging = false;
double dragStartX = 0;
double dragStartY = 0;
float dragStartCx = centerX;
float dragStartCy = centerY;

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

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseButtonCallback(GLFWwindow* w, int button, int action, int /*mods*/) {
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (action == GLFW_PRESS) {
        static double lastClickTime = 0.0;
        double now = glfwGetTime();

        if (now - lastClickTime < 0.3) {
            // Double-click: zoom in on point
            double mx, my;
            glfwGetCursorPos(w, &mx, &my);
            float re, im;
            screenToComplex(w, mx, my, re, im);
            centerX = re;
            centerY = im;
            zoom *= 0.35f;
            maxIter = std::min(2000, (int)(maxIter * 1.3f));
            dragging = false;
            lastClickTime = -1.0; // prevent triple-click triggering again
            return;
        }
        lastClickTime = now;

        dragging    = true;
        dragStartCx = centerX;
        dragStartCy = centerY;
        glfwGetCursorPos(w, &dragStartX, &dragStartY);

    } else if (action == GLFW_RELEASE) {
        dragging = false;
    }
}

void cursorPosCallback(GLFWwindow* w, double xpos, double ypos) {
    if (!dragging) return;
    int W, H;
    glfwGetFramebufferSize(w, &W, &H);
    float scale = 2.0f / ((float)W * zoom);
    centerX = dragStartCx - (float)(xpos - dragStartX) * scale;  // - not +
    centerY = dragStartCy + (float)(ypos - dragStartY) * scale;  // + not -
}

void scrollCallback(GLFWwindow* w, double deltaX, double deltaY) {
    double mx, my;
    glfwGetCursorPos(w, &mx, &my);

    bool pinching = glfwGetKey(w, GLFW_KEY_LEFT_CONTROL)  == GLFW_PRESS ||
                    glfwGetKey(w, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

    if (pinching) {
        // Trackpad pinch zoom
        float re, im;
        screenToComplex(w, mx, my, re, im);
        float factor = std::exp((float)deltaY * 0.1f);
        zoomToward(re, im, factor);
    } else if (std::abs(deltaX) > 0.01) {
        // Trackpad two finger scroll
        int W, H;
        glfwGetFramebufferSize(w, &W, &H);
        float scale = 2.0f / ((float)W * zoom);
        centerX -= (float)deltaX * scale * 8.0f;
        centerY += (float)deltaY * scale * 8.0f;
    } else {
        // Mouse scroll wheel: zoom toward cursor
        float re, im;
        screenToComplex(w, mx, my, re, im);
        float factor = std::pow(1.15f, (float)deltaY);
        zoomToward(re, im, factor);
    }
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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

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