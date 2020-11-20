#include "EventCenter.hpp"

namespace Lafez {
    LzShrPtr<EventCenter> EventCenter::getInstance() {
        static LzShrPtr<EventCenter> instance{ nullptr };
        if (instance == nullptr) {
            instance = std::make_shared<EventCenter>();
        }

        return instance;
    }

    void EventCenter::emit(Event& event) {
        LzVec<uint16_t> indices{ };
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

    void EventCenter::flush() {
        mSubscriptions.clear();
        mDied.clear();
    }

    LzShrPtr<EventSubscription> EventCenter::subscribe(const LzFunc<void, Event&>& callback) {
        return mSubscriptions.emplace_back(std::make_shared<EventSubscription>(callback));
    }

    void EventCenter::cleanUp() {
        if (mDied.empty()) return;

        if (mDied.size() == mSubscriptions.size()) {
            flush();
            return;
        }

        // move all dead subs to the end
        std::size_t right = mSubscriptions.size() - 1;
        for (const auto& idx : mDied) {
            if (idx >= right) break;

            while (!mSubscriptions[right]->isAlive() && right > idx + 1) {
                --right;
            }

            if (mSubscriptions[right]->isAlive()) {
                std::swap(mSubscriptions[idx], mSubscriptions[right]);
            } else {
                break;
            }
        }

        // remove all dead subs
        mSubscriptions.erase(mSubscriptions.end() - mDied.size(),
                             mSubscriptions.end());

        mDied.clear();
    }

    std::size_t EventCenter::subscriptionCount() const {
        return mSubscriptions.size();
    }
}