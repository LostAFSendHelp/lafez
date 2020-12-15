#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafez/utils/Log.hpp>
#include <lafezlib_export.h>

namespace Lafez {
    class LAFEZLIB Input {
    public:
        virtual ~Input() = default;



        /**
         * @brief Get input state for a key in a single frame
         * 
         * @param keycode The corresponding keycode
         * @return true if the key receives any input (press, release, repeat) during that frame
         * @return false otherwise
         */
        static bool getKey(int keycode);



        /**
         * @brief Get the position of the mouse within the window
         * 
         * @return LzPair<float, float> 
         */
        static LzPair<float, float> getMousePosition();



        /**
         * @brief Initialize the Singleton Input object of a specific implementation T
         * 
         * @tparam T The implementation of the input to be initialized
         * @tparam Args Deduced
         * @param args The constructor arguments of the implementation
         */
        template<typename T, typename ... Args>
        static void startUp(Args&& ...args);



        /**
         * @brief Terminate the current Singleton Input object and set the pointer to nullptr
         * 
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
        Input() = default;

        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;
        virtual bool getKeyImpl(int keycode) const = 0;
        virtual LzPair<float, float> getMousePositionImpl() const = 0;

    private:
        static LzUniPtr<Input> sShared;
    };



    template<typename T, typename ... Args>
    void Input::startUp(Args&& ...args) {
        if (Input::sShared != nullptr) {
            LZ_ENGINE_WARN("ATTEMPT TO RE-STARTUP NON-NULL INPUT INSTANCE, ABORTING...");
            return;
        }

        Input::sShared = std::make_unique<T>(std::forward<Args>(args)...);
        Input::sShared->initImpl();
    }
};