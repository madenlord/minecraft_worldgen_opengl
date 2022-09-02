#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

#include "window.hpp"

Window::~Window()
{
    glfwTerminate();
}

int Window::init() 
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    /* We disable mouse cursor whenever we are inside the window */
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return 0;
}

void Window::updateDeltaTime() 
{
    _currentFrame = glfwGetTime();
    _deltaTime = _currentFrame - _lastFrame;
    _lastFrame = _currentFrame;
}