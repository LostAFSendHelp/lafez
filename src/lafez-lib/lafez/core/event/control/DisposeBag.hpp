#pragma once
#include <lafez/lafez_pch.hpp>
#include "EventSubscription.hpp"

namespace Lafez {
    class LAFEZLIB DisposeBag final {
    public:

        /**
         * @brief Construct a new Dispose Bag object, used to manage Event Subscriptions to avoid bad access
         */
        DisposeBag() = default;



        /**
         * @brief Destroy the Dispose Bag object
         */
        ~DisposeBag();

        
        
        /**
         * @brief Add an Event Subscription to a managed collection. Kills all managed subscriptions on dtor call
         * 
         * @param subscription 
         */
        void dispose(const LzShrPtr<EventSubscription>& subscription);



        /**
         * @brief Manually kills all managed subscriptions. Also automatically called on dtor call
         */
        void dump();



        /**
         * @brief The number of subscriptions currently held, which will be killed when dump() is called. For debugging use only
         * 
         * @return std::size_t 
         */
        std::size_t subscriptionCount() const;

    private:
        LzShrPtrVec<EventSubscription> mSubscriptions;
    };
};