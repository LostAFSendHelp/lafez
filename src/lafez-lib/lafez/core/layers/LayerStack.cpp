#include <lafez/utils/Log.hpp>
#include "LayerStack.hpp"

namespace Lafez {
    LayerStack::LayerStack() {

    }

    LayerStack::~LayerStack() {
        flush();
    }

    void LayerStack::pushLayer(const LzShrPtr<Layer>& layer) {
        if (!layer) return;

        for (const auto& _layer : mLayers) {
            if (_layer->mID == layer->mID) {
                LZ_ENGINE_WARN("[ABORTED] Attempting to push Layer already in stack");
                return;
            }
        }

        mLayers.push_back(layer);
        layer->onAttach();
    }

    LzShrPtr<Layer> LayerStack::popLayer() {
        if (mLayers.empty()) return nullptr;
        auto popped = mLayers.back();
        popped->onDetach();
        mLayers.pop_back();

        return popped;
    }

    LzShrPtrVec<Layer> LayerStack::removeByTag(const LzString& tag) {
        LzShrPtrVec<Layer> removed{ };
        mLayers.remove_if([tag, &removed](const LzShrPtr<Layer>& layer) {
            if (layer->mTag == tag) {
                layer->onDetach();
                removed.push_back(layer);
                return true;
            }

            return false;
        });

        return removed;
    }

    LzShrPtr<Layer> LayerStack::removeById(uint8_t id) {
        LzShrPtr<Layer> removed{ nullptr };

        for (const auto& layer : mLayers) {
            if (layer->mID == id) {
                removed = layer;
                removed->onDetach();
                mLayers.remove(layer);
                break;
            }
        }

        return removed;
    }

    LzShrPtrVec<Layer> LayerStack::findByTag(const LzString& tag) const {
        LzShrPtrVec<Layer> found{ };
        
        for (const auto& layer : mLayers) {
            if (layer->mTag == tag) {
                found.push_back(layer);
            }
        }

        return found;
    }

    LzShrPtr<Layer> LayerStack::findById(uint8_t id) const {
        for (const auto& layer : mLayers) {
            if (layer->mID == id) {
                return layer;
            }
        }

        return nullptr;
    }

    void LayerStack::onEvent(Event& event) const {
        if (mLayers.empty()) return;

        auto it = mLayers.rbegin();
        while (it != mLayers.rend() && !event.isHandled()) {
            const auto& layer = *it;
            if (layer->mIsEnabled) {
                layer->onEvent(event);
            }

            ++it;
        }
    }

    void LayerStack::update() const {
        for (const auto& layer : mLayers) {
            if (layer->mIsEnabled) {
                layer->onUpdate();
            }
        }
    }

    void LayerStack::flush() {
        while (!mLayers.empty()) {
            mLayers.back()->onDetach();
            mLayers.pop_back();
        }
    }
}