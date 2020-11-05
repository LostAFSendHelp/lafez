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
        const long mID;

        virtual ~Event();

        virtual bool isOfCategory(EventCategory category) const = 0;
    
    protected:
        EventType mType;
        bool mHandled;

        Event(EventType type);

    private:
        static long sCount;
    };
};