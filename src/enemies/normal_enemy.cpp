#include "normal_enemy.hpp"
#include "../utils/app_constants.hpp"

NormalEnemy::NormalEnemy(const Vector4f& body, float x, float y)
    : Enemy(body, x, y, NORMAL_ENEMY_MAX_HP, NORMAL_ENEMY_SPEED, true, NORMAL_ENEMY_VALUE) {

}
