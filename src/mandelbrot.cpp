#include "mandelbrot.h"
#include "canvas2d.h"
#include "complexscreen.h"
#include <glad/glad.h>
#include <memory>

int maxIter = 256;

void mandelbrotRenderCallback(std::shared_ptr<Canvas2D> canvas) {
    if (!canvas.get()->getShaderProgram()->getProgram().has_value()) return;
    unsigned int prog = canvas.get()->getShaderProgram()->getProgram().value();

    glUniform2f(glGetUniformLocation(prog, "u_center"), centerX, centerY);
    glUniform1f(glGetUniformLocation(prog, "u_zoom"), zoom);
    glUniform1i(glGetUniformLocation(prog, "u_maxIter"), maxIter);
}