#include "glm/ext/matrix_transform.hpp"

#include "cube.hpp"

/* ========================================================================
 * =====================  VERTEX & INDICES DEFINITION ===================== 
 * ========================================================================
*/
namespace cubecommon 
{
    std::vector<Vertex> vertices = 
    {
        /* Position */                        /* Texture coords */ 

        // Front face
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)},   // 0 (down left)
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f)},    // 1 (down right)
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f)},     // 2 (up right)
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)},    // 3 (up left)

        // Left face
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},   // 4 (down left)
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f)},    // 5 (down right)
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f)},     // 6 (up right)
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},    // 7 (up left)

        // Right face
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)},   // 8 (down left)
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)},    // 9 (down right)
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},     // 10 (up right)
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)},    // 11 (up left)

        // Bottom face
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)},   // 12 (down left)
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f)},    // 13 (down right)
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},     // 14 (up right)
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},    // 15 (up left)

        // Back face
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},   // 16 (down left)
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)},    // 17 (down right)
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},     // 18 (up right)
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},    // 19 (up left)

        // Top face
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f)},   // 20 (down left)
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f)},    // 21 (down right)
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},     // 22 (up right)
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},    // 23 (up left)
    };

    std::vector<unsigned int> indices = 
    {
        0, 1, 2, 
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10, 
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };   
}

/* ========================================================================
 * ====================  CUBE CLASS METHODS DEFINITION ==================== 
 * ========================================================================
*/

/* Static member declaration & initialization */
Mesh* Cube::_mesh = nullptr;
unsigned int Cube::_instances = 0;

/* Function declaration */
Cube::Cube(const glm::vec3& position, Shader* shader, Texture* texture)
{
    /* Common mesh for all cubes initialization */
    if(_mesh == nullptr || _instances == 0)
        _mesh = new Mesh(cubecommon::vertices, cubecommon::indices);

    _shader    = shader;
    _texture   = texture;
    _transform = glm::translate(_transform, position);
    _instances++;
}

Cube::~Cube()
{
    _instances--;
    if(_instances == 0)
        delete _mesh;
}

void Cube::draw(Renderer& renderer)
{
    _shader->setUniformMat4f("u_M", _transform);
    renderer.draw(_mesh->getVertexArray(), _mesh->getIndexBuffer(), *_shader);
}
