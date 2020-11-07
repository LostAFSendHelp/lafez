#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez-pch.hpp>

namespace Lafez {
    enum class EventCategory: uint8_t {
        None,
        Application,
        Input,
        MouseInput,
        KeyInput,
    };

    enum class EventType: uint8_t {
        None,
        KeyUp = 10, KeyDown, KeyRepeat,
        MouseUp = 20, MouseDown, MouseMove, MouseScroll,
        WindowResize = 30, WindowClose
    };

    class LAFEZLIB Event {
    public:

        /**
         * @brief The ID of the Event object
        */
        const long mID;



        /**
         * @brief Destroy the Event object
         */
        virtual ~Event();

        
        
        /**
         * @brief Check whether the Event belongs to the specified category. One Event can belong to multiple categories
         * 
         * @param category The category to check
         * @return true if the Event object belongs to the given category
         * @return false otherwise
         */
        virtual bool isOfCategory(EventCategory category) const = 0;
        
        
        
        /**
         * @brief Check whether the Event is already handled
         * 
         * @return true if already handled
         * @return false otherwise
         */
        virtual bool isHandled() const;



        /**
         * @brief Get the Type of the event object
         * 
         * @return EventType 
         */
        virtual EventType getType() const;



        /**
         * @brief Mark the event object as already handled
         */
        virtual void handle();
    
    protected:
        EventType mType;
        bool mIsHandled;

        Event(EventType type);

    private:
        static long sCount;
    };
};