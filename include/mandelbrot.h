#pragma once

#include "canvas2d.h"
#include "imgui.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>

// Runs every frame
void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas);

// ImGUI window
void mandelbrotGUI();