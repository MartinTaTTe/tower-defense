#pragma once

#include "enemy.hpp"

class RegenEnemy : public Enemy {
public:
    RegenEnemy(const Vector4f& body, float x, float y);
};
