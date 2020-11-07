#pragma once
#include "Event.hpp"

namespace Lafez {
    using EventCallback = std::function<void(Event&)>;

    class LAFEZLIB EventSubscription final {
    public:

        /**
         * @brief The ID of the subscription
         */
        const uint16_t mID;



        /**
         * @brief Construct a new Event Subscription object. Event Subscriptions with ref captures should be disposed by a DisposeBag or handled with care
         * 
         * @param callback the callback to handle the emitted Event
         */
        EventSubscription(EventCallback callback);



        /**
         * @brief Destroy the Event Subscription object
         */
        ~EventSubscription();

        
        
        /**
         * @brief Trigger the callback on the emitted event
         * 
         * @param event the Event to be processed
         */
        void dispatch(Event& event) const;



        /**
         * @brief Mark the subscription as dead. A dead subscription will not be dispatched when an Event is emitted. A dead subscription is removed from the Event Center after each iteration
         */
        void die();



        /**
         * @brief Whether the subscription has died
         * 
         * @return true if it is dead
         * @return false otherwise
         */
        bool isAlive() const;

    private:
        EventCallback mCallback;
        bool mIsAlive;
        static uint16_t sCount;
    };
};