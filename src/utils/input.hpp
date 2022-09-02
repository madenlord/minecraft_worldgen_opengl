#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input 
{
    private:
        GLFWwindow* _window;
        /*
         * Cursor coordinates to check mouse movement
         */
        float _sensitivity = 0.1f;
        bool _firstMouse = true;
        double _lastX;
        double _lastY;
        float _yaw   = -90.0f;
        float _pitch = 0.0f;

    public:
        Input(GLFWwindow* window) 
            : _window(window) {}
        ~Input() {}

        int getKey(int keycode) const { return glfwGetKey(_window, keycode); }
        bool isKeyPressed(int keycode) const { return getKey(keycode) == GLFW_PRESS || getKey(keycode) == GLFW_REPEAT; }
        glm::vec3 calculateCursorDirection(double xpos, double ypos);
        bool isMouseMoving(double *xpos, double *ypos);
 
};

#endif