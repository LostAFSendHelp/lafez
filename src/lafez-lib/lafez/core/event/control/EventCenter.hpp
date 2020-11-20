#pragma once
#include "EventSubscription.hpp"

namespace Lafez {
    class LAFEZLIB EventCenter final {
    public:

        /**
         * @brief Construct a new Event Center object, which receives and propagates event to subscribers
         */
        EventCenter() = default;



        /**
         * @brief Destroy the Event Center object
         */
        ~EventCenter() = default;



        /**
         * @brief Emit an event to all subscribers so they can handle with a callback
         * 
         * @param event the event to be notified of
         */
        void emit(Event& event);



        /**
         * @brief Remove all subscriptions
         */
        void flush();



        /**
         * @brief Subscribe to the Event Center to get notified when a Event is emitted.
         * 
         * @param callback The handler for the emitted event
         * @return LzShrPtr<EventSubscription> 
         */
        LzShrPtr<EventSubscription> subscribe(const LzFunc<void, Event&>& callback);



        /**
         * @brief Number of currently held subscriptions, for debugging use only
         * 
         * @return std::size_t 
         */
        std::size_t subscriptionCount() const;



        /**
         * @brief The EventCenter singleton
         * 
         * @return LzShrPtr<EventCenter> 
         */
        static LzShrPtr<EventCenter> getInstance();

    private:
        LzShrPtrVec<EventSubscription> mSubscriptions;
        LzVec<uint16_t> mDied;

        void cleanUp();
    };
};