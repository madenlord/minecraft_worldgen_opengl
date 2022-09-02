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
        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 _forward  = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 _up       = glm::vec3(0.0f, 1.0f, 0.0f);

        /* Frustum & projection properties */
        float _fovY;
        float _aspectRatio;
        float _near;
        float _far;

        /* Camera movement attributes */
        float _speed = 100.0f;

        glm::mat4 _view;
        glm::mat4 _projection;
        glm::mat4 _viewProjection;

    public:
        Camera(float fovY, float aspectRatio, float near, float far)
            : _fovY(fovY), _aspectRatio(aspectRatio), _near(near), _far(far),
              _view(glm::lookAt(_position, _position + _forward, _up)),
              _projection(glm::perspective(glm::radians(_fovY), _aspectRatio, _near, _far)),
              _viewProjection(_projection * _view) {} 
        ~Camera() {}

        void processInput(Window& window, Input& input);

        /* Getters & Setters */
        const glm::vec3& getPosition() { return _position; }
        void setPosition(const glm::vec3& position) { _position = position; }

        const glm::vec3& getForward() { return _forward; }
        void setForward(const glm::vec3& forward) { _forward = forward; }

        const glm::vec3& getUp() { return _up; }

        float getFovY() const { return _fovY; }

        float getAspectRatio() const { return _aspectRatio; }

        float getNear() const { return _near; }

        float getFar() const { return _far; }

        const glm::mat4& getProjection() { return _projection; }
        void setProjection(const glm::mat4& projection) { _projection = projection; }

        const glm::mat4& getView() { return _view; }
        void setView(const glm::mat4& view) { _view = view; }

        glm::mat4& getViewProjection();

    private:
        void recalculateViewMatrix();
};

#endif