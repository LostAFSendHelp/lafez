#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>

#define LZT_KEY             ::Lafez::EventType::Key
#define LZT_MOUSE_BUTTON    ::Lafez::EventType::MouseButton
#define LZT_MOUSE_MOVE      ::Lafez::EventType::MouseMove
#define LZT_MOUSE_SCROLL    ::Lafez::EventType::MouseScroll
#define LZT_WINDOW_RESIZE   ::Lafez::EventType::WindowResize
#define LZT_WINDOW_CLOSE    ::Lafez::EventType::WindowClose
#define LZT_NONE            ::Lafez::EventType::None

#define LZC_KEY             ::Lafez::EventCategory::KeyInput
#define LZC_MOUSE           ::Lafez::EventCategory::MouseInput
#define LZC_INPUT           ::Lafez::EventCategory::Input
#define LZC_APPLICATION     ::Lafez::EventCategory::Application
#define LZC_NONE            ::Lafez::EventCategory::None

#define LZ_MOUSE_LEFT       ::Lafez::MouseButton::Left
#define LZ_MOUSE_RIGHT      ::Lafez::MouseButton::Right
#define LZ_MOUSE_MID        ::Lafez::MouseButton::Mid
#define LZ_MOUSE_UNKNOWN    ::Lafez::MouseButton::Unknown

#define LZ_BUTTON_PRESS     ::Lafez::ButtonAction::Press
#define LZ_BUTTON_RELEASE   ::Lafez::ButtonAction::Release
#define LZ_BUTTON_REPEAT    ::Lafez::ButtonAction::Repeat
#define LZ_BUTTON_UNKNOWN   ::Lafez::ButtonAction::Unknown

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
        Key,
        MouseButton,
        MouseMove,
        MouseScroll,
        WindowResize, 
        WindowClose
    };

    enum class MouseButton: uint8_t {
        Unknown,
        Left, Right, Mid
    };

    enum class ButtonAction: uint8_t {
        Unknown,
        Release, Press, Repeat
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