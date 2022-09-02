#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GLFW/glfw3.h>
#include "glm/vec3.hpp"

class Window 
{
    private:
        GLFWwindow* mWindow;
        unsigned int mWidth;
        unsigned int mHeight;
        const char* mTitle;

        /* 
         * Delta time variables, being Delta time the time between current
         * frame and last frame
         */
        float mDeltaTime;
        float mCurrentFrame;
        float mLastFrame;

    public:
        Window(unsigned int width, unsigned int height, const char* title)
            : mWidth(width), mHeight(height), mTitle(title),
              mDeltaTime(0.0f), mLastFrame(0.0f) {};
        ~Window();

        /* Window and frame operations */
        int init();
        void updateDeltaTime();
        unsigned char windowShouldClose() const { return glfwWindowShouldClose(mWindow); }
        void swapBuffers() const { glfwSwapBuffers(mWindow); }
        void pollEvents() const { glfwPollEvents(); }
        
        /* Getters & Setters */
        GLFWwindow* getGLFWwindow() const { return mWindow; }
        unsigned int getWidth() const { return mWidth; }
        unsigned int getHeight() const { return mHeight; } 
        std::string getTitle() const { return mTitle; }
        float getDeltaTime() const { return mDeltaTime; }
};

#endif