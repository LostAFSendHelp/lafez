#pragma once
#include <lafezlib_export.h>
#include <glm/glm.hpp>

namespace Lafez {

    /********************************************************
    *                        Camera                         *
    ********************************************************/

    class LAFEZLIB Camera {
    public:

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



        /**
         * @brief Get the position of the camera in the world coordinate system
         * 
         * @return const glm::vec3& 
         */
        const glm::vec3& getPosition() const;

    protected:
        static const glm::vec3 sUp;
        glm::vec3 mPosition;

    private:

    };



    /********************************************************
    *                  PerspectiveCamera                    *
    ********************************************************/

    class LAFEZLIB PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(const glm::vec3& position, const glm::vec3& target, const glm::mat4& perspective);
        ~PerspectiveCamera() = default;

        glm::mat4 getViewMatrix() const override;
        glm::mat4 getProjectionMatrix() const override;
        glm::mat4 getViewProjectionMatrix() const override;



        /**
         * @brief Rotate the camera around the Y axis, aka { .0f, 1.0f, .0f }. Must be called between a beginTransformation() call and an endTransformation() call, otherwise throw a runtime exception
         * 
         * @param radians The angle by which to rotate the camera
         */
        void rotateV(float radians);



        /**
         * @brief Rotate the camera around the `right` vector, aka the normal to the front-up plane. Must be called between a beginTransformation() call and an endTransformation() call, otherwise throw a runtime exception
         * 
         * @param radians The angle by which to rotate the camera
         */
        void rotateH(float radians);



        /**
         * @brief Translate the position of the camera. Must be called between a beginTransformation() call and an endTransformation() call, otherwise throw a runtime exception
         * 
         * @param translation The translation by which to translate the camera
         */
        void translate(const glm::vec3 translation);



        /**
         * @brief Signal the beginning of a transformation. Only after this is called can `translate` and `rotate` can be executed
         */
        void beginTransformation();



        /**
         * @brief Signal the completion of a transformation, upon which the view and view-projection matrices are recalculated. After this, every call to transformation functions `translate` and `rotate` throws a runtime exception, until beginTransformation() is called again
         */
        void endTransformation();

    private:
        glm::mat4 mView;
        glm::mat4 mPerspective;
        glm::mat4 mViewProjection;
        glm::vec3 mFront;
        glm::vec3 mRight;
        glm::vec3 mUp;

        bool mIsTransforming;

        void recalculateMatrices();
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