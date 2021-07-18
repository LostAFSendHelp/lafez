#pragma once 
#include <lafez/utils/Log.hpp>
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>
#include "WindowInfo.hpp"

namespace Lafez {
    class LAFEZLIB Window {
    public:
        virtual ~Window();



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
         * @brief Get the Name of the window, which is displayed on the title bar
         * 
         * @return const LzString& 
         */
        static const LzString& getName();



        /**
         * @brief Set the Name of the window, which changes the displayed name on the title bar accordingly
         * 
         * @param name the new name to be set for the window
         */
        static void setName(const char* name);



        /**
         * @brief Whether the window should close in the next iteration
         */
        static bool shouldClose();



        /**
         * @brief Process all messages on the window message queue per frame
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
        Window(const char* name, uint16_t width, uint16_t height);

        virtual uint16_t getWidthImpl() const = 0;          // TODO: decide whether this should be non-pure
        virtual uint16_t getHeightImpl() const = 0;         // TODO: decide whether this should be non-pure
        virtual const LzString& getNameImpl() const = 0;    // TODO: decide whether this should be non-pure
        virtual void setNameImpl(const char* name) = 0;
        virtual void* getWindowPointerImpl() const = 0;
        virtual bool shouldCloseImpl() const = 0;
        virtual void closeImpl() = 0;
        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;
        virtual void updateImpl() = 0;

        WindowInfo* mWindowInfo;

    private:
        static LzUniPtr<Window> sShared;
    };



    template<typename T, typename ... Args>
    void Window::startUp(Args&& ...args) {
        LZ_ENGINE_GUARD_VOID((sShared == nullptr), "ATTEMPT TO RE-STARTUP NON-NULL WINDOW INSTANCE, ABORTING...");

        Window::sShared = std::make_unique<T>(std::forward<Args>(args)...);
        Window::sShared->initImpl();
    }
};