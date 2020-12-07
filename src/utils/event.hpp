#pragma once
/*
Events are used to communicate between the levels in the component hierarchy.
This class MUST NOT include any classes that are not base classes.
*/
#include <stdint.h>

#include "../gui/drawable.hpp"

enum EventType : int8_t {
    None,
    PopState,
    PushGameState,
    PushInputState,
    PushMapEditorState,
    MouseMovement,
    MouseClick,
    MouseClickReleased,
    Resize,
    ChangeMapSize,
    SelectTile,
    Dead,
    Save,
    Start,
    End,
    Pause,
    SendWave,
    DamageEnemy,
    SelectTower
};

enum TileType : int8_t;
class Enemy;

struct Event
{
    Event(EventType type = EventType::None) : type(type) { }
    EventType type;
    union {
        struct {
            int x, y;
            char tower_type;
        };
        struct {
            float damage;
            Enemy* enemy;
        };
        Vector2i coords;
        Vector2i increments;
        Vector4i body;
        TileType tileType;
        bool condition;
    };
};
