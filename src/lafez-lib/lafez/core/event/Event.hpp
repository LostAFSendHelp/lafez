#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>

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
        MouseUp = 20, MouseDown, MouseScroll,
        MouseMove = 30,
        WindowResize = 40, 
        WindowClose = 50
    };

    enum class MouseButton: uint8_t {
        Unknown,
        Left, Right, Mid
    };

    class LAFEZLIB Event {
    public:

        /**
         * @brief The Type of the event. Each event can only be of ONE type
         */
        const EventType mType;



        /**
         * @brief Destroy the Event object
         */
        virtual ~Event();



        /**
         * @brief Check whether the Event belongs to a set of categories
         * 
         * @tparam Args 
         * @param args 
         * @return true 
         * @return false 
         */
        template<typename ... Args>
        bool isOfCategories(Args ... args) const;
        
        
        
        /**
         * @brief Check whether the Event is already handled
         * 
         * @return true if already handled
         * @return false otherwise
         */
        virtual bool isHandled() const;



        /**
         * @brief Mark the event object as already handled
         */
        virtual void handle();



        /**
         * @brief Debug information of the Event
         * -
         * @return std::string& 
         */
        virtual std::string toString() const = 0;
    
    protected:
        bool mIsHandled;

        Event(EventType type);

        
        
        /**
         * @brief Check whether the Event belongs to the specified category. One Event can belong to multiple categories
         * 
         * @param category The category to check
         * @return true if the Event object belongs to the given category
         * @return false otherwise
         */
        virtual bool isOfCategory(EventCategory category) const = 0;

    private:

    };

    template<typename ... Args>
    bool Event::isOfCategories(Args ... args) const {
        return (... && isOfCategory(args));
    }
};