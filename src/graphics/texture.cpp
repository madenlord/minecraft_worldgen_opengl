#include <glad/glad.h>

#include "stb_image.h"
#include "texture.hpp"

Texture::Texture(const std::string& path)
    : _filepath(path), _localBuffer(nullptr), _width(0), _height(0), _BPP(0)
{
    stbi_set_flip_vertically_on_load(1);    // Porque las coordenadas de OpenGL suelen ser contrarias a las de PNG
    _localBuffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 4);
    glGenTextures(1, &_rendererID);
    glBindTexture(GL_TEXTURE_2D, _rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(_localBuffer)
        stbi_image_free(_localBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_rendererID);
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _rendererID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
