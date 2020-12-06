#pragma once

#include "enemy.hpp"

class RegenEnemy : public Enemy {
public:
    RegenEnemy(const Vector4i& body, float x, float y);
};
