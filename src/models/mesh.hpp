#ifndef MESH_H
#define MESH_H

#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"

class Mesh
{
    private:
        VertexArray* _vao;
        VertexBuffer* _vbo;
        IndexBuffer* _ibo;

    public:
        Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
        ~Mesh();

        void bind() const;
        void unbind() const;

        VertexArray& getVertexArray() const { return *_vao; }
        VertexBuffer& getVertexBuffer() const { return *_vbo; }
        IndexBuffer& getIndexBuffer() const { return *_ibo; }
};

#endif