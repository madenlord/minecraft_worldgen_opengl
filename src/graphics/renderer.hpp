#ifndef RENDERER_H
#define RENDERER_H

#include "vertexArray.hpp"
#include "indexBuffer.hpp"
#include "shader.hpp"

class Renderer 
{
    public:
        void clear() const;
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};

#endif