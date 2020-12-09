#include "fast_enemy.hpp"
#include "../utils/app_constants.hpp"

FastEnemy::FastEnemy(const Vector4f& body, float x, float y, char type)
    : Enemy(body, x, y, FAST_ENEMY_MAX_HP, FAST_ENEMY_SPEED, true, FAST_ENEMY_VALUE, type, T_FAST_ENEMY) {

}