#include "glm/matrix.hpp"

#include <GLFW/glfw3.h>
#include "camera.hpp"

void Camera::processInput(Window& window, Input& input)
{
    float cameraSpeed = mSpeed * window.getDeltaTime();

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
        mForward = input.calculateCursorDirection(xpos, ypos);
    
    /* Basic WASD input */
    if(input.isKeyPressed(GLFW_KEY_W))     // Move forward
        mPosition += cameraSpeed * mForward;
    if(input.isKeyPressed(GLFW_KEY_S))     // Move back
        mPosition -= cameraSpeed * mForward;
    if(input.isKeyPressed(GLFW_KEY_A))     // Move left
        mPosition -= glm::normalize(glm::cross(mForward, mUp)) * cameraSpeed;
    if(input.isKeyPressed(GLFW_KEY_D))     // Move right
        mPosition += glm::normalize(glm::cross(mForward, mUp)) * cameraSpeed;

    /* Up & Down (flying) input */
    if(input.isKeyPressed(GLFW_KEY_SPACE)) // Move up
        mPosition += cameraSpeed * mUp;
    if(input.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
        mPosition -= cameraSpeed * mUp;
}

void Camera::recalculateViewMatrix()
{
    mView           = glm::lookAt(mPosition, mPosition + mForward, mUp);
    mViewProjection = mProjection * mView;
}

glm::mat4& Camera::getViewProjection()
{
    recalculateViewMatrix();
    return mViewProjection;
}