#pragma once

#include "enemy.hpp"

class FlyingEnemy : public Enemy {
public:
    FlyingEnemy(const Vector4i& body, float x, float y);
};
