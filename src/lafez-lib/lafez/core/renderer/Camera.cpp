#include "Camera.hpp"

namespace Lafez {

    /********************************************************
    *                        Camera                         *
    ********************************************************/

    Camera::Camera(const glm::vec3& position):
    mPosition(position) {

    }



    /********************************************************
    *                   PerspectiveCamera                   *
    ********************************************************/

    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::mat4& perspective):
    Camera(position),
    mPerspective(perspective),
    mView(1.0f),
    mViewProjection(1.0f) {

    }

    glm::mat4 PerspectiveCamera::getViewMatrix() const {
        return mView;
    }

    glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
        return mPerspective;
    }

    glm::mat4 PerspectiveCamera::getViewProjectionMatrix() const {
        return mViewProjection;
    }

    

    /********************************************************
    *                   OrthographicCamera                  *
    ********************************************************/

    // TODO: Properly implement this
    OrthographicCamera::OrthographicCamera(const glm::vec3& position):
    Camera(position) {

    }

    // TODO: Properly implement this
    glm::mat4 OrthographicCamera::getViewMatrix() const {
        return glm::mat4{ 1.0f };
    }

    // TODO: Properly implement this
    glm::mat4 OrthographicCamera::getProjectionMatrix() const {
        return glm::mat4{ 1.0f };
    }

    // TODO: Properly implement this
    glm::mat4 OrthographicCamera::getViewProjectionMatrix() const {
        return glm::mat4{ 1.0f };
    }
}