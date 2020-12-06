#pragma once

#include "enemy.hpp"

class SpawnEnemy : public Enemy {
public:
    SpawnEnemy(const Vector4i& body, float x, float y);
};