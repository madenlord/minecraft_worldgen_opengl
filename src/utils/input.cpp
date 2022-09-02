#include "input.hpp"

bool Input::isMouseMoving(double *xpos, double *ypos)
{
    glfwGetCursorPos(mWindow, xpos, ypos);
    if(mFirstMouse)
    {
        mLastX = *xpos;
        mLastY = *ypos;
        mFirstMouse = false;
    }

    if(*xpos != mLastX || *ypos != mLastY)
        return true;

    return false;
}

glm::vec3 Input::calculateCursorDirection(double xpos, double ypos)
{
    float xoffset = (xpos - mLastX) * mSensitivity;
    float yoffset = (mLastY - ypos) * mSensitivity;

    mLastX = xpos;
    mLastY = ypos;

    mYaw   += xoffset;
    mPitch += yoffset;

    /* To avoid users to look further than the sky or their feet */
    if(mPitch > 89.0f)
        mPitch = 89.0f;
    if(mPitch < -89.0f)
        mPitch = -89.0f;

    glm::vec3 cursorDirection;
    cursorDirection.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    cursorDirection.y = sin(glm::radians(mPitch));
    cursorDirection.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    return glm::normalize(cursorDirection);
}