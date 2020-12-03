#pragma once
/*
Events are used to communicate between the levels in the component hierarchy.
*/
#include <stdint.h>

#include "../game/state.hpp"
#include "../gui/drawable.hpp"

enum EventType : int8_t;

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
        Vector2f coords;
        Vector4i body;
    };
};
