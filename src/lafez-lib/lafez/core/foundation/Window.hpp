#pragma once 
#include <lafez/utils/Log.hpp>
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

namespace Lafez {
    class LAFEZLIB Window {
    public:
        virtual ~Window() = default;



        /**
         * @brief Get the Height of the window
         * 
         * @return uint16_t 
         */
        static uint16_t getHeight();



        /**
         * @brief Get the Width of the window
         * 
         * @return uint16_t 
         */
        static uint16_t getWidth();



        /**
         * @brief Get the Name of the window
         * 
         * @return const LzString& 
         */
        static const LzString& getName();



        /**
         * @brief Whether the window should close in the next iteration
         */
        static bool shouldClose();



        /**
         * @brief Update the window object each frame
         */
        static void update();



        /**
         * @brief Set the window close flag to TRUE
         */
        static void close();



        /**
         * @brief Get the underlying pointer to the window object
         * 
         * @return void* 
         */
        static void* getWindowPointer();



        /**
         * @brief Get the Window object
         * 
         * @return LzShrPtr<Window> 
         */
        static LzShrPtr<Window> getWindow();



        /**
         * @brief Initialize the Singleton Window object of a specific implementation T
         * 
         * @tparam T The implementation of the window to be initialized
         * @tparam Args Deduced
         * @param args The constructor arguments of the implementation
         */
        template<typename T, typename ... Args>
        static void startUp(Args&& ...args);



        /**
         * @brief Terminate the current Singleton Window object and set it to nullptr
         */
        static void shutDown();



        /**
         * @brief Whether the Singleton object is present or nullptr
         * 
         * @return true if the Singleton object is initialized and has not been terminated (by calling shutDown())
         * @return false if the Singleton object is nullptr (startUp() not called or shutDown() just called)
         */
        static bool isInitialized();




    protected:
        Window() = default;

        virtual uint16_t getWidthImpl() const = 0;
        virtual uint16_t getHeightImpl() const = 0;
        virtual const LzString& getNameImpl() const = 0;
        virtual void* getWindowPointerImpl() const = 0;
        virtual bool shouldCloseImpl() const = 0;
        virtual void closeImpl() = 0;
        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;
        virtual void updateImpl() = 0;

    private:
        static LzShrPtr<Window> sShared;
    };



    template<typename T, typename ... Args>
    void Window::startUp(Args&& ...args) {
        LZ_ENGINE_GUARD_VOID((sShared == nullptr), "ATTEMPT TO RE-STARTUP NON-NULL WINDOW INSTANCE, ABORTING...");

        Window::sShared = std::make_shared<T>(std::forward<Args>(args)...);
        Window::sShared->initImpl();
    }
};