#pragma once
#include "EventSubscription.hpp"

namespace Lafez {
    class LAFEZLIB EventCenter final {
    public:
        EventCenter() = default;
        ~EventCenter() = default;

        void emit(Event& event);
        std::shared_ptr<EventSubscription> subscribe(EventCallback callback);

    private:
        std::vector<std::shared_ptr<EventSubscription>> mSubscriptions;
        std::vector<uint16_t> mDied;

        void cleanUp();
    };
};