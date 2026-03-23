#include "canvas2d.h"
#include <glad/glad.h>
#include <iostream>

// Full-screen quad
const float Canvas2D::verts[] = {
    1.0f,  1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,   // bottom right
    -1.0f, -1.0f, 0.0f,  // bottom left
    -1.0f,  1.0f, 0.0f   // top left 
};

const unsigned int Canvas2D::indices[] = {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

Canvas2D::Canvas2D(const std::filesystem::path& fragPath, std::function<void(std::shared_ptr<Canvas2D>)> renderCallback) 
: renderCallback(renderCallback) {
    shaderProgram = std::make_shared<ShaderProgram>("../shaders/default.vert", fragPath);
    if (!shaderProgram.get()->getProgram().has_value()) {
        std::cout << "Encountered errors while compiling shaders" << std::endl;
        return;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);

    initSuccessful = true;
}

void Canvas2D::loop() {
    if (!shaderProgram.get()->getProgram().has_value()) return;

    glUseProgram(shaderProgram.get()->getProgram().value());

    renderCallback(shared_from_this());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Canvas2D::~Canvas2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}