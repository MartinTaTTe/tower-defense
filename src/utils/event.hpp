#pragma once
#include <stdint.h>
#include "../game/state.hpp"

typedef std::pair<float, float> Coords;

enum EventType : int8_t {
    PushState,
    PopState,
    MouseMovement,
    MouseClick
};

struct Event
{
    EventType type;
    union {
        State* state;
        Coords coords;
    };
};

