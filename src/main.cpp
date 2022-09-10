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

#include "cube.hpp"

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

    /* Camera */
    Camera camera(90.0f, (float)window.getWidth()/(float)window.getHeight(), 0.01f, 1000.0f);

    /* Shader */
    Shader shader("../res/shaders/Basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.4f, 0.32f, 0.25f, 1.0f); 
    shader.setUniformMat4f("u_VP", camera.getViewProjection());

    /* Textures */
    Texture texture("../res/textures/pop_cat.png");
    texture.bind();     // De forma predeterminada, la textura irá al slot 0
    shader.setUniform1i("u_texture", 0);    // el 0 corresponde al slot que estamos usando ahora

    /* Cube */
    Cube defaultCube(glm::vec3(0.0f, 0.0f, 0.0f), &shader, &texture);

    /* Unbind all OpenGL objects */
    shader.unbind();
    defaultCube.unbind();

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
        shader.setUniformMat4f("u_VP", camera.getViewProjection());

        /* OpenGL Objects drawing */
        defaultCube.draw(renderer);

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        window.pollEvents();
    }

    window.~Window();
    return 0;
}