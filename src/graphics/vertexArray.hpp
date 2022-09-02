#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray 
{
    private:
        unsigned int _rendererID;

    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;
};

#endif