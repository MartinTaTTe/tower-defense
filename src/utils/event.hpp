#pragma once
#include <stdint.h>
#include "../game/state.hpp"
#include "../gui/drawable.hpp"

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
    Event(EventType type) : type(type) { }
    Event() = delete;
    EventType type;
    union {
        State* state;
        Vector2f coords;
        Vector4i body;
    };
};

