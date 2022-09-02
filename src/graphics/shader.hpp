#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        std::string _filepath;
        unsigned int _rendererID;
        std::unordered_map<std::string, unsigned int> _uniformLocationCache;

        public:
            Shader(const std::string& filepath);
            ~Shader();

            void bind() const;
            void unbind() const;

            void setUniform1i(const std::string& name, int value);
            void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
            void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

        private:
            unsigned int compileShader(unsigned int type, const std::string& source);
            ShaderProgramSource parseShader(const std::string& filepath);
            unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
            unsigned int getUniformLocation(const std::string& name);
};

#endif