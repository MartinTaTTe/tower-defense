#include "regen_enemy.hpp"
#include "../utils/app_constants.hpp"

RegenEnemy::RegenEnemy(const Vector4f& body, float x, float y)
    : Enemy(body, x, y, REGEN_ENEMY_MAX_HP, REGEN_ENEMY_SPEED, true, REGEN_ENEMY_VALUE, T_REGEN_ENEMY) {

}