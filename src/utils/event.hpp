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
    PushMapSelectState,
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
    SelectTower,
    AddGold,
    SpawnKill
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
        struct {
            float x_f, y_f;
        };
        Vector2f position;
        Vector2i increments;
        Vector4f body;
        TileType tileType;
        bool condition;
    };
};
