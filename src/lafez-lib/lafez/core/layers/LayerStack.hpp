#pragma once
#include <lafez/lafez_pch.hpp>
#include "Layer.hpp"

namespace Lafez {
    class LAFEZLIB LayerStack final {
    public:

        /**
         * @brief LayerStack object to act as a container for layers. Top-most layer gets rendered last and fed events first
         */
        LayerStack();



        /**
         * @brief Destroy the Layer Stack object
         */
        ~LayerStack();



        /**
         * @brief Push a Layer onto the top of the stack. Call Layer::onAttach() upon completion
         * 
         * @param layer The Layer object to be pushed onto the stack
         */
        void pushLayer(const LzShrPtr<Layer>& layer);



        /**
         * @brief Remove the top-most Layer object from the stack. Call Layer::onDetach() before removal
         */
        LzShrPtr<Layer> popLayer();



        /**
         * @brief Remove all Layer objects with the specified tag. Call Layer::onDetach() before each removal
         * 
         * @param tag The tag of the Layers to be removed
         * @return LzShrPtrVec<Layer> 
         */
        LzShrPtrVec<Layer> removeByTag(const LzString& tag);



        /**
         * @brief Remove one Layer object with the specified unique ID. Call Layer::onDetach() before removal
         * 
         * @param id The ID of the Layer to be removed
         * @return LzShrPtr<Layer>, nullptr if none is found (removed)
         */
        LzShrPtr<Layer> removeById(uint8_t id);



        /**
         * @brief Find all Layer objects with the specified tag
         * 
         * @param tag The tag of the Layers to be retrieved
         * @return LzShrPtrVec<Layer> 
         */
        LzShrPtrVec<Layer> findByTag(const LzString& tag) const;



        /**
         * @brief Find the Layer object with the specified unique ID
         * 
         * @param id The ID of the Layer to be retrieved
         * @return LzShrPtr<Layer>, nullptr if none is found
         */
        LzShrPtr<Layer> findById(uint8_t id) const;



        /**
         * @brief Propagate an Event object down the stack. The top-most layer is the first to be fed
         * 
         * @param event The event to be propagated down the stack
         */
        void onEvent(Event& event) const;



        /**
         * @brief Remove all Layer objects, calling onDetach per removal
         */
        void flush();

    private:
        LzShrPtrList<Layer> mLayers;
    };
};