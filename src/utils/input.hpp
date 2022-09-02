#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input 
{
    private:
        GLFWwindow* mWindow;
        /*
         * Cursor coordinates to check mouse movement
         */
        float mSensitivity = 0.1f;
        bool mFirstMouse = true;
        double mLastX;
        double mLastY;
        float mYaw   = -90.0f;
        float mPitch = 0.0f;

    public:
        Input(GLFWwindow* window) 
            : mWindow(window) {}
        ~Input() {}

        int getKey(int keycode) const { return glfwGetKey(mWindow, keycode); }
        bool isKeyPressed(int keycode) const { return getKey(keycode) == GLFW_PRESS || getKey(keycode) == GLFW_REPEAT; }
        glm::vec3 calculateCursorDirection(double xpos, double ypos);
        bool isMouseMoving(double *xpos, double *ypos);
 
};

#endif