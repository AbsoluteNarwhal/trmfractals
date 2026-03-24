#pragma once

#include "mandelbrot.h"
#include "canvas2d.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>

// Mandelbrot parameters (uniforms)
extern float centerX;
extern float centerY;
extern float zoom;
extern int maxIter;

// Converts screen coordinates (px, py) into complex coordinates (re, im)
void screenToComplex(GLFWwindow* w, double px, double py, float& re, float& im);

// Zoom towards a complex coordinate (updates u_zoom uniform)
void zoomToward(float re, float im, float factor);

// Runs every frame
void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas);