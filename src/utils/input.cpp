#include "input.hpp"

bool Input::isMouseMoving(double *xpos, double *ypos)
{
    glfwGetCursorPos(_window, xpos, ypos);
    if(_firstMouse)
    {
        _lastX = *xpos;
        _lastY = *ypos;
        _firstMouse = false;
    }

    if(*xpos != _lastX || *ypos != _lastY)
        return true;

    return false;
}

glm::vec3 Input::calculateCursorDirection(double xpos, double ypos)
{
    float xoffset = (xpos - _lastX) * _sensitivity;
    float yoffset = (_lastY - ypos) * _sensitivity;

    _lastX = xpos;
    _lastY = ypos;

    _yaw   += xoffset;
    _pitch += yoffset;

    /* To avoid users to look further than the sky or their feet */
    if(_pitch > 89.0f)
        _pitch = 89.0f;
    if(_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 cursorDirection;
    cursorDirection.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    cursorDirection.y = sin(glm::radians(_pitch));
    cursorDirection.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    return glm::normalize(cursorDirection);
}