#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GLFW/glfw3.h>
#include "glm/vec3.hpp"

class Window 
{
    private:
        GLFWwindow* _window;
        unsigned int _width;
        unsigned int _height;
        const char* _title;

        /* 
         * Delta time variables, being Delta time the time between current
         * frame and last frame
         */
        float _deltaTime;
        float _currentFrame;
        float _lastFrame;

    public:
        Window(unsigned int width, unsigned int height, const char* title)
            : _width(width), _height(height), _title(title),
              _deltaTime(0.0f), _lastFrame(0.0f) {};
        ~Window();

        /* Window and frame operations */
        int init();
        void updateDeltaTime();
        unsigned char windowShouldClose() const { return glfwWindowShouldClose(_window); }
        void swapBuffers() const { glfwSwapBuffers(_window); }
        void pollEvents() const { glfwPollEvents(); }
        
        /* Getters & Setters */
        GLFWwindow* getGLFWwindow() const { return _window; }
        unsigned int getWidth() const { return _width; }
        unsigned int getHeight() const { return _height; } 
        std::string getTitle() const { return _title; }
        float getDeltaTime() const { return _deltaTime; }
};

#endif