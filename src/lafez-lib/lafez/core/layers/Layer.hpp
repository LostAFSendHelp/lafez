#pragma once
#include <lafezlib_export.h>
#include <lafez/core/lafez_event.hpp>

namespace Lafez {
    class LAFEZLIB Layer {
    public:

        friend class LayerStack;



        /**
         * @brief The unique ID of the Layer
         */
        const uint8_t mID;



        /**
         * @brief The name of the Layer for debugging purposes
         */
        const std::string mTag;


        /**
         * @brief Whether the Layer is up for consuming Events. Defaulted to TRUE
         */
        bool mIsEnabled;



        /**
         * @brief Whether the render objects on the Layer should be rendered. Defaulted to FALSE
         */
        bool mIsHidden;



        /**
         * @brief A Layer object to act as an container for game objects. Objects on the same layer are rendered/fed events by the Layer one after another.
         * 
         * @param name the name of the Layer, for debugging purposes
         */
        Layer(const char *name = "LafezLayer");



        /**
         * @brief Destroy the Layer object
         */
        virtual ~Layer();



    protected:

        /**
         * @brief Called by LayerStack when first attached to the stack
         */
        virtual void onAttach();
        
        
        
        /**
         * @brief Called by LayerStack just before being detached from the stack
         * 
         */
        virtual void onDetach();



        /**
         * @brief Consume the event propagated by LayerStack
         * 
         * @param event 
         */
        virtual void onEvent(Event& event) const;




    private:
        static uint8_t sCount;
    };
};