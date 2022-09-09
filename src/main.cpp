#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>

#include "window.hpp"
#include "input.hpp"
#include "camera.hpp"

#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "renderer.hpp"

int main(void)
{
    Window window(1920, 1080, "3D OpenGL Graphs");
    if(window.init() == -1) 
    {
        return -1;
    }
    Input input(window.getGLFWwindow());

    /*
     * ===================================================================
     * =========================== OPENGL CODE ===========================
     * ===================================================================
     */

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

    VertexArray vao;

    VertexBuffer vbo(vertices); 

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo(indices);

    /* Camera */
    Camera camera(90.0f, (float)window.getWidth()/(float)window.getHeight(), 0.01f, 1000.0f);

    /* Shader */
    Shader shader("../res/shaders/Basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.4f, 0.32f, 0.25f, 1.0f); 
    shader.setUniformMat4f("u_MVP", camera.getViewProjection());

    /* Textures */
    Texture texture("../res/textures/pop_cat.png");
    texture.bind();     // De forma predeterminada, la textura irá al slot 0
    shader.setUniform1i("u_texture", 0);    // el 0 corresponde al slot que estamos usando ahora

    /* Unbind all OpenGL objects */
    shader.unbind();
    vao.unbind();
    ibo.unbind();

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!window.windowShouldClose())
    {
        /* Render here */
        renderer.clear();

        /* Update Delta time */
        window.updateDeltaTime();

        /* Window color */
        glClearColor(0.47f, 0.8f, 1.0f, 1.0f);

        /* Move camera according to the user input */
        camera.processInput(window, input);

        shader.bind();
        shader.setUniform4f("u_color", 0.4f, 0.32f, 0.25f, 1.0f); 
        shader.setUniformMat4f("u_MVP", camera.getViewProjection());

        /* OpenGL Objects drawing */
        renderer.draw(vao, ibo, shader);

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        window.pollEvents();
    }

    window.~Window();
    return 0;
}