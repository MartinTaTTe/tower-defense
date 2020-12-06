#include "flying_enemy.hpp"
#include "../utils/app_constants.hpp"

FlyingEnemy::FlyingEnemy(const Vector4i& body, float x, float y)
    : Enemy(body, x, y, FLYING_ENEMY_MAX_HP, FLYING_ENEMY_SPEED, false) {

}