#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "shader.hpp"

Shader::Shader(const std::string& filepath)
    : _filepath(filepath), _rendererID(0)
{
    ShaderProgramSource source = parseShader(filepath);
    std::cout << "VERTEX SHADER: " << std::endl;
    std::cout << source.VertexSource << std::endl;
    _rendererID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(_rendererID);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    return program;
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
    if(_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    int location = glGetUniformLocation(_rendererID, name.c_str());
    if(location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist" << std::endl;

    _uniformLocationCache[name] = location;

    return location;
}

void Shader::bind() const 
{
    glUseProgram(_rendererID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}