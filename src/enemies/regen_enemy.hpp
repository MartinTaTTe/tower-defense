#pragma once

#include "enemy.hpp"

class RegenEnemy : public Enemy {
public:
    RegenEnemy(const Vector4f& body, float x, float y);
    Event Update(float damage, float d_x_, float d_y_, float tile_width, float tile_height) override;
};
