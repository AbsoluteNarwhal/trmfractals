#include "mandelbrot.h"
#include "canvas2d.h"
#include "complexscreen.h"
#include "imgui.h"
#include <glad/glad.h>
#include <memory>

int maxIter = 256;
int doColour = 1;

void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas) {
    if (!canvas.get()->getShaderProgram()->getProgram().has_value()) return;
    unsigned int prog = canvas.get()->getShaderProgram()->getProgram().value();

    glUniform2f(glGetUniformLocation(prog, "u_center"), centerX, centerY);
    glUniform1f(glGetUniformLocation(prog, "u_zoom"), zoom);
    glUniform1i(glGetUniformLocation(prog, "u_maxIter"), maxIter);
    glUniform1i(glGetUniformLocation(prog, "u_doColour"), doColour);
}

void mandelbrotGUI(ImGuiIO& io) {
    ImGui::Begin("Mandelbrot Set Settings");
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Checkbox("Draw divergent colours", (bool*) &doColour);
    ImGui::End();
}