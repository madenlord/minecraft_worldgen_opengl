#include <glad/glad.h>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
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