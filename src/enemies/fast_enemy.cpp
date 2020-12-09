#include "fast_enemy.hpp"
#include "../utils/app_constants.hpp"

FastEnemy::FastEnemy(const Vector4f& body, float x, float y)
    : Enemy(body, x, y, FAST_ENEMY_MAX_HP, FAST_ENEMY_SPEED, true, FAST_ENEMY_VALUE, T_FAST_ENEMY) {

}