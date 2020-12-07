#pragma once

#include "enemy.hpp"

class NormalEnemy : public Enemy {
public:
    NormalEnemy(const Vector4f& body, float x, float y);
};
