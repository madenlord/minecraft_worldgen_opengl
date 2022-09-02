#include <glad/glad.h>

#include "stb_image.h"
#include "texture.hpp"

Texture::Texture(const std::string& path)
    : mFilepath(path), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0)
{
    stbi_set_flip_vertically_on_load(1);    // Porque las coordenadas de OpenGL suelen ser contrarias a las de PNG
    mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);
    glGenTextures(1, &mRendererID);
    glBindTexture(GL_TEXTURE_2D, mRendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(mLocalBuffer)
        stbi_image_free(mLocalBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &mRendererID);
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
