#pragma once
#include <lafez/lafez-pch.hpp>
#include "EventSubscription.hpp"

namespace Lafez {
    class DisposeBag final {
    public:
        DisposeBag() = default;
        ~DisposeBag();

        void dispose(const std::shared_ptr<EventSubscription>& subscription);
        void dump();

    private:
        std::vector<std::shared_ptr<EventSubscription>> mSubscriptions;
    };
};