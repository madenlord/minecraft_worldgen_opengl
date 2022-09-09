#include "glm/matrix.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"

Camera::Camera(float fovY, float aspectRatio, float near, float far)
                : _fovY(fovY), _aspectRatio(aspectRatio), _near(near), _far(far),
                  _view(glm::lookAt(_position, _position + _forward, _up)),
                  _projection(glm::perspective(glm::radians(_fovY), _aspectRatio, _near, _far)),
                  _viewProjection(_projection * _view) 
{
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Camera::processInput(Window& window, Input& input)
{
    float cameraSpeed = _speed * window.getDeltaTime();

    /* If ESCAPE is pressed, the window is closed */
    if(input.isKeyPressed(GLFW_KEY_ESCAPE))
        window.~Window();

    /* If shift is pressed, we sprint */
    if(input.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        cameraSpeed *= 2.5f;

    /* Mouse input */
    double xpos;
    double ypos;
    if(input.isMouseMoving(&xpos, &ypos))
        _forward = input.calculateCursorDirection(xpos, ypos);
    
    /* Basic WASD input */
    if(input.isKeyPressed(GLFW_KEY_W))     // Move forward
        _position += cameraSpeed * _forward;
    if(input.isKeyPressed(GLFW_KEY_S))     // Move back
        _position -= cameraSpeed * _forward;
    if(input.isKeyPressed(GLFW_KEY_A))     // Move left
        _position -= glm::normalize(glm::cross(_forward, _up)) * cameraSpeed;
    if(input.isKeyPressed(GLFW_KEY_D))     // Move right
        _position += glm::normalize(glm::cross(_forward, _up)) * cameraSpeed;

    /* Up & Down (flying) input */
    if(input.isKeyPressed(GLFW_KEY_SPACE)) // Move up
        _position += cameraSpeed * _up;
    if(input.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
        _position -= cameraSpeed * _up;
}

void Camera::recalculateViewMatrix()
{
    _view           = glm::lookAt(_position, _position + _forward, _up);
    _viewProjection = _projection * _view;
}

glm::mat4& Camera::getViewProjection()
{
    recalculateViewMatrix();
    return _viewProjection;
}