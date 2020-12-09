#include "flying_enemy.hpp"
#include "../utils/app_constants.hpp"

FlyingEnemy::FlyingEnemy(const Vector4f& body, float x, float y, char type)
    : Enemy(body, x, y, FLYING_ENEMY_MAX_HP, FLYING_ENEMY_SPEED, false, FLYING_ENEMY_VALUE, type, T_FLYING_ENEMY) {

}