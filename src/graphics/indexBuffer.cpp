#include <glad/glad.h>

#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
    : _count(indices.size()), _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GL_UNSIGNED_INT), indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &_rendererID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
