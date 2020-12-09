#pragma once

#include "enemy.hpp"

class FastEnemy : public Enemy {
public:
    FastEnemy(const Vector4f& body, float x, float y);
};