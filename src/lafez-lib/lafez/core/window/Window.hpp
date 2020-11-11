#pragma once 
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

namespace Lafez {
    class LAFEZLIB Window {
    public:
        virtual ~Window();



        /**
         * @brief Get the Height of the window
         * 
         * @return uint16_t 
         */
        virtual uint16_t getHeight() const = 0;



        /**
         * @brief Get the Width of the window
         * 
         * @return uint16_t 
         */
        virtual uint16_t getWidth() const = 0;



        /**
         * @brief Get the Name of the window
         * 
         * @return const std::string& 
         */
        virtual const std::string& getName() const = 0;



        /**
         * @brief Whether the window should close in the ne--xt iteration
         */
        virtual bool shouldClose() const = 0;



        /**
         * @brief Initialize the window. Must be called before other window functions can be called
         */
        virtual void init() = 0;



        /**
         * @brief Terminate the window object
         */
        virtual void terminate() = 0;



        /**
         * @brief Update the window object each frame
         */
        virtual void update() const = 0;



        /**
         * @brief Set the window close flag to TRUE
         */
        virtual void close() = 0;



        static Window* createWindow(const char* name, uint16_t width, uint16_t height);

    protected:
        Window();

    private:
    };
};