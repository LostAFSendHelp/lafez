#include "DisposeBag.hpp"

namespace Lafez {
    DisposeBag::~DisposeBag() {
        dump();
    }

    void DisposeBag::dispose(const std::shared_ptr<EventSubscription>& subscription) {
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
}