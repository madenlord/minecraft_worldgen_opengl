#include <glad/glad.h>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex>& data)
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}