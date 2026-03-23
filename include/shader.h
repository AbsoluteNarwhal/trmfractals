#pragma once

#include <filesystem>
#include <optional>
#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::filesystem::path& vertPath, const std::filesystem::path& fragPath);
    inline std::optional<unsigned int> getProgram() { return program; }

private:
    std::string vertexSrc, fragmentSrc;
    unsigned int vertexShader, fragmentShader;
    std::optional<unsigned int> program;
};