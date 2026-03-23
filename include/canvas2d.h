#pragma once

#include "shader.h"
#include <memory>
#include <filesystem>
#include <functional>

// A full-screen quad
class Canvas2D : public std::enable_shared_from_this<Canvas2D> {
public:
    Canvas2D(const std::filesystem::path& fragPath, std::function<void(std::shared_ptr<Canvas2D>)> renderCallback);
    void loop();
    ~Canvas2D();
    inline std::shared_ptr<ShaderProgram> getShaderProgram() { return shaderProgram; }

    bool initSuccessful = false;

private:
    static const float verts[];
    static const unsigned int indices[];
    std::shared_ptr<ShaderProgram> shaderProgram;
    unsigned int VBO, VAO, EBO;
    std::function<void(std::shared_ptr<Canvas2D>)> renderCallback;
};