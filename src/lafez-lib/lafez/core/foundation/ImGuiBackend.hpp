#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>
#include <lafez-imgui/imgui.h>

namespace Lafez {
    class LAFEZLIB ImGuiBackend {
    public:
        virtual ~ImGuiBackend() = default;



        /**
         * @brief Call Init on the ImGui backend implementation
         */
        static void init();



        /**
         * @brief Call Shutdown on the ImGui backend implementation
         */
        static void terminate();



        /**
         * @brief Call NewFrame on the ImGui backend implementation
         */
        static void newFrame();



        /**
         * @brief Call RenderDrawData on the ImGui backend implementation
         */
        static void renderDrawData(ImDrawData* data);



        /**
         * @brief Initialize the ImGuiBackend Singleton object to the specified implementation
         * 
         * @tparam T The concrete implementation of the ImGuiBackend
         * @tparam Args deduced
         * @param args The constructor arguments of the implementation
         */
        template<typename T, typename ... Args>
        static void startUp(Args&& ...args);



        /**
         * @brief Terminate the ImGuiBackend Singleton object and set the pointer to nullptr
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
        ImGuiBackend() = default;

        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;
        virtual void newFrameImpl() = 0;
        virtual void renderDrawDataImpl(ImDrawData* data) = 0;

    private:
        static LzUniPtr<ImGuiBackend> sShared;
    };



    template<typename T, typename ... Args>
    void ImGuiBackend::startUp(Args&& ...args) {
        LZ_ENGINE_GUARD_VOID((sShared == nullptr), "ATTEMPT TO RE-STARTUP NON-NULL IMGUIBACKEND INSTANCE, ABORTING...");

        ImGuiBackend::sShared = std::make_unique<T>(std::forward<Args>(args)...);
    }
};