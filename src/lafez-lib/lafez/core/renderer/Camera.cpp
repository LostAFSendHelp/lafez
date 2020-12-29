#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <lafez/lafez_pch.hpp>

namespace Lafez {

    /********************************************************
    *                        Camera                         *
    ********************************************************/

    const glm::vec3 Camera::sUp{ .0f, 1.0f, .0f };

    Camera::Camera(const glm::vec3& position):
    mPosition(position) {

    }

    const glm::vec3& Camera::getPosition() const {
        return mPosition;
    }



    /********************************************************
    *                   PerspectiveCamera                   *
    ********************************************************/

    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& target, const glm::mat4& perspective):
    Camera(position),
    mPerspective(perspective),
    mView(1.0f),
    mViewProjection(1.0f),
    mFront(glm::normalize(mPosition - target)),
    mRight(1.0f),
    mUp(Camera::sUp),
    mIsTransforming(false) {
        mRight = glm::normalize(glm::cross(mUp, mFront));
        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mViewProjection = mPerspective * mView;
    }

    glm::mat4 PerspectiveCamera::getViewMatrix() const {
        LZ_ENGINE_GUARD_FATAL(!mIsTransforming, "Attempting to access view matrics mid-transformation");
        return mView;
    }

    glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
        LZ_ENGINE_GUARD_FATAL(!mIsTransforming, "Attempting to access view matrics mid-transformation");
        return mPerspective;
    }

    glm::mat4 PerspectiveCamera::getViewProjectionMatrix() const {
        LZ_ENGINE_GUARD_FATAL(!mIsTransforming, "Attempting to access view matrics mid-transformation");
        return mViewProjection;
    }

    void PerspectiveCamera::rotateH(float radians) {
        LZ_ENGINE_GUARD_FATAL(mIsTransforming, "Attempting to tranform without transformation initiation");
        mFront = glm::rotate(mFront, radians, mRight);
        mUp = glm::normalize(glm::cross(mFront, mRight));
    }

    void PerspectiveCamera::rotateV(float radians) {
        LZ_ENGINE_GUARD_FATAL(mIsTransforming, "Attempting to tranform without transformation initiation");
        mFront = glm::rotate(mFront, radians, Camera::sUp);
        mRight = glm::normalize(glm::cross(mUp, mFront));
    }

    void PerspectiveCamera::translate(const glm::vec3 translation) {
        LZ_ENGINE_GUARD_FATAL(mIsTransforming, "Attempting to tranform without transformation initiation");
        mPosition += translation;
    }

    void PerspectiveCamera::beginTransformation() {
        mIsTransforming = true;
    }

    void PerspectiveCamera::endTransformation() {
        mIsTransforming = false;
        recalculateMatrices();
    }

    void PerspectiveCamera::recalculateMatrices() {
        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mViewProjection = mPerspective * mView;
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