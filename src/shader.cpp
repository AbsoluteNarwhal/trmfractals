#include "shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::filesystem::path& vertPath, const std::filesystem::path& fragPath) {
    if (!std::filesystem::exists(vertPath) || !std::filesystem::exists(fragPath)) {
        std::cout << "Warning: shader file not found" << std::endl;
        program = std::nullopt;
        return;
    }

    std::ifstream tVert(vertPath);
    std::stringstream ssVert;
    ssVert << tVert.rdbuf();
    vertexSrc = ssVert.str();

    std::ifstream tFrag(fragPath);
    std::stringstream ssFrag;
    ssFrag << tFrag.rdbuf();
    fragmentSrc = ssFrag.str();

    // Compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertTextCStr = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &vertTextCStr, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Shader '" << vertPath.string() << "': vertex shader compilation failed: " << infoLog << std::endl;
        program = std::nullopt;
        return;
    }

    // Compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragTextCStr = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragTextCStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Shader '" << fragPath.string() << "': fragment shader compilation failed: " << infoLog << std::endl;
        program = std::nullopt;
        return;
    }

    // Link shaders
    program = glCreateProgram();
    glAttachShader(program.value(), vertexShader);
    glAttachShader(program.value(), fragmentShader);
    glLinkProgram(program.value());

    glGetProgramiv(program.value(), GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(program.value(), 512, NULL, infoLog);
        std::cout << "Failed to link shaders: " << infoLog << std::endl;
        program = std::nullopt;
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    if (program.has_value()) 
        glDeleteProgram(program.value());
}