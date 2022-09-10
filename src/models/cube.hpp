#ifndef CUBE_H
#define CUBE_H

#include <vector>

#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"
#include "indexBuffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "renderer.hpp"
#include "mesh.hpp"

class Cube
{
    private:
        static Mesh* _mesh;
        static unsigned int _instances;

        Shader* _shader;
        Texture* _texture;
        glm::mat4 _transform = glm::mat4(1.0f);
        
    public:
        Cube(const glm::vec3& position, Shader* shader, Texture* texture);
        ~Cube();

        void bind() const { _mesh->bind(); }
        void unbind() const { _mesh->unbind(); }

        void draw(Renderer& renderer);
};


#endif