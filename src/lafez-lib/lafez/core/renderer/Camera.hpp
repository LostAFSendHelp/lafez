#pragma once
#include <lafezlib_export.h>
#include <glm/glm.hpp>

namespace Lafez {

    /********************************************************
    *                        Camera                         *
    ********************************************************/

    class LAFEZLIB Camera {
    public:

        /// The current position of the camera in the world coordinate system
        glm::vec3 mPosition;



        /**
         * @brief Construct a new Camera object
         * 
         * @param position The position to initialize the camera at
         */
        Camera(const glm::vec3& position);



        /**
         * @brief Destroy the Camera object
         * 
         */
        virtual ~Camera() = default;

        

        /**
         * @brief Get the view matrix of the camera
         * 
         * @return glm::mat4 
         */
        virtual glm::mat4 getViewMatrix() const = 0;



        /**
         * @brief Get the projection matrix of the camera
         * 
         * @return glm::mat4 
         */
        virtual glm::mat4 getProjectionMatrix() const = 0;



        /**
         * @brief Get the view projection matrix of the camera
         * 
         * @return glm::mat4 
         */
        virtual glm::mat4 getViewProjectionMatrix() const = 0;

    private:

    };



    /********************************************************
    *                  PerspectiveCamera                    *
    ********************************************************/

    class LAFEZLIB PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(const glm::vec3& position, const glm::mat4& perspective);
        ~PerspectiveCamera() = default;

        glm::mat4 getViewMatrix() const override;
        glm::mat4 getProjectionMatrix() const override;
        glm::mat4 getViewProjectionMatrix() const override;

    private:
        glm::mat4 mView;
        glm::mat4 mPerspective;
        glm::mat4 mViewProjection;
    };



    /********************************************************
    *                  OrthographicCamera                   *
    ********************************************************/

    class LAFEZLIB OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const glm::vec3& position);
        ~OrthographicCamera() = default;

        glm::mat4 getViewMatrix() const override;
        glm::mat4 getProjectionMatrix() const override;
        glm::mat4 getViewProjectionMatrix() const override;

    private:
    };
};