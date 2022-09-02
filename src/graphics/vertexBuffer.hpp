#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture;
};

class VertexBuffer
{
    private:
        unsigned int mRendererID;

    public:
        VertexBuffer(std::vector<Vertex>& vertices);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
};

#endif