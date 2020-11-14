#include "EventCenter.hpp"

namespace Lafez {
    std::shared_ptr<EventCenter> EventCenter::getInstance() {
        static std::shared_ptr<EventCenter> instance{ nullptr };
        if (instance == nullptr) {
            instance = std::make_shared<EventCenter>();
        }

        return instance;
    }

    void EventCenter::emit(Event& event) {
        std::vector<uint16_t> indices{ };
        for (uint16_t idx = 0; idx < mSubscriptions.size(); ++idx) {
            auto sub = mSubscriptions[idx];
            if (!sub->isAlive()) {
                mDied.push_back(idx);
                continue;
            } else if (!event.isHandled()) {
                sub->dispatch(event);
            }
        }

        cleanUp();
    }

    std::shared_ptr<EventSubscription> EventCenter::subscribe(EventCallback callback) {
        return mSubscriptions.emplace_back(std::make_shared<EventSubscription>(callback));
    }

    void EventCenter::cleanUp() {
        if (mDied.empty()) return;

        for (const auto& idx : mDied) {
            mSubscriptions[idx] = *(mSubscriptions.end() - 1);
            mSubscriptions.pop_back();
        }

        mDied.clear();
    }
}