#pragma once

#include "shader.h"
#include <memory>
#include <filesystem>

// A full-screen quad
class Canvas2D {
public:
    Canvas2D(const std::filesystem::path& fragPath);
    void loop();

    bool initSuccessful = false;
    
private:
    static float verts[];
    static unsigned int indices[];
    std::unique_ptr<ShaderProgram> shaderProgram;
    unsigned int VBO, VAO, EBO;
};