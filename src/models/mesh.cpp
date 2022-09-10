#include <vector>

#include "vertexBufferLayout.hpp"
#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) 
{
    _vao = new VertexArray();
    _vbo = new VertexBuffer(vertices);
    
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    _vao->addBuffer(*_vbo, layout);

    _ibo = new IndexBuffer(indices);
}

Mesh::~Mesh()
{
    delete _vao;
    delete _vbo;
    delete _ibo;
}

void Mesh::bind() const
{
    _vao->bind();
    _ibo->bind();
}

void Mesh::unbind() const
{
    _vao->unbind();
    _ibo->unbind();
}