#include "fast_enemy.hpp"
#include "../utils/app_constants.hpp"

FastEnemy::FastEnemy(const Vector4i& body, float x, float y)
    : Enemy(body, x, y, FAST_ENEMY_MAX_HP, FAST_ENEMY_SPEED, true) {

}