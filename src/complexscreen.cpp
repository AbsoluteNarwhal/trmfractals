#include "complexscreen.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cmath>

// Offset/zoom parameters (uniforms)
float centerX = -0.5;
float centerY = 0.0;
float zoom = 0.65;

// Dragging (touchpad or mouse)
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

void mouseButtonCallback(GLFWwindow* w, int button, int action, int /*mods*/) {
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (action == GLFW_PRESS) {
        dragging = true;
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
    centerX = dragStartCx - (float)(xpos - dragStartX) * scale;
    centerY = dragStartCy + (float)(ypos - dragStartY) * scale;
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