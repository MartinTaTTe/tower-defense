#pragma once
/*
Events are used to communicate between the levels in the component hierarchy.
This class MUST NOT include any classes that are not base classes.
*/
#include <stdint.h>

#include "../gui/drawable.hpp"

class State;

enum EventType : int8_t {
    None,
    PushState,
    PopState,
    MouseMovement,
    MouseClick,
    Resize
};

struct Event
{
    Event(EventType type = EventType::None) : type(type) { }
    EventType type;
    union {
        State*   state;
        Vector2i coords;
        Vector4i body;
    };
};
