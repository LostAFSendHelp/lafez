#include "DisposeBag.hpp"

namespace Lafez {
    DisposeBag::~DisposeBag() {
        dump();
    }

    void DisposeBag::dispose(const LzShrPtr<EventSubscription>& subscription) {
        for (const auto& sub : mSubscriptions) {
            if (sub->mID == subscription->mID) {
                return;
            }
        }

        mSubscriptions.push_back(subscription);
    }

    void DisposeBag::dump() {
        for (auto& sub : mSubscriptions) {
            sub->die();
        }

        mSubscriptions.clear();
    }

    std::size_t DisposeBag::subscriptionCount() const {
        return mSubscriptions.size();
    }
}