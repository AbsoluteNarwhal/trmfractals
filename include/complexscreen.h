#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

extern float centerX;
extern float centerY;
extern float zoom;

// Converts screen coordinates (px, py) into complex coordinates (re, im)
void screenToComplex(GLFWwindow* w, double px, double py, float& re, float& im);

// Zoom towards a complex coordinate (updates u_zoom uniform)
void zoomToward(float re, float im, float factor);

// On mouse click (drag)
void mouseButtonCallback(GLFWwindow* w, int button, int action, int /*mods*/);

// On mouse move (drag)
void cursorPosCallback(GLFWwindow* w, double xpos, double ypos);

// On mouse scroll (zoom)
void scrollCallback(GLFWwindow* w, double deltaX, double deltaY);