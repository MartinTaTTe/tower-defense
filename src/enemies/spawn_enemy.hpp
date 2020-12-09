#pragma once

#include "enemy.hpp"

class SpawnEnemy : public Enemy {
public:
    SpawnEnemy(const Vector4f& body, float x, float y);
};