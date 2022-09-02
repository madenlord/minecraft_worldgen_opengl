#include <glad/glad.h>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_rendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}