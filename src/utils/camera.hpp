#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "window.hpp"
#include "input.hpp"

class Camera
{
    private:
        /* Position & Orientation of the camera */
        glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 mForward  = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 mUp       = glm::vec3(0.0f, 1.0f, 0.0f);

        /* Frustum & projection properties */
        float mFOVy;
        float mAspectRatio;
        float mNear;
        float mFar;

        /* Camera movement attributes */
        float mSpeed = 100.0f;

        glm::mat4 mView;
        glm::mat4 mProjection;
        glm::mat4 mViewProjection;

    public:
        Camera(float fovY, float aspectRatio, float near, float far)
            : mFOVy(fovY), mAspectRatio(aspectRatio), mNear(near), mFar(far),
              mView(glm::lookAt(mPosition, mPosition + mForward, mUp)),
              mProjection(glm::perspective(glm::radians(mFOVy), mAspectRatio, mNear, mFar)),
              mViewProjection(mProjection * mView) {} 
        ~Camera() {}

        void processInput(Window& window, Input& input);

        /* Getters & Setters */
        const glm::vec3& getPosition() { return mPosition; }
        void setPosition(const glm::vec3& position) { mPosition = position; }

        const glm::vec3& getForward() { return mForward; }
        void setForward(const glm::vec3& forward) { mForward = forward; }

        const glm::vec3& getUp() { return mUp; }

        float getFovY() const { return mFOVy; }

        float getAspectRatio() const { return mAspectRatio; }

        float getNear() const { return mNear; }

        float getFar() const { return mFar; }

        const glm::mat4& getProjection() { return mProjection; }
        void setProjection(const glm::mat4& projection) { mProjection = projection; }

        const glm::mat4& getView() { return mView; }
        void setView(const glm::mat4& view) { mView = view; }

        glm::mat4& getViewProjection();

    private:
        void recalculateViewMatrix();
};

#endif