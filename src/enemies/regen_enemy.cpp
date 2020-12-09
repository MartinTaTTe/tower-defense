#include "regen_enemy.hpp"
#include "../utils/app_constants.hpp"

RegenEnemy::RegenEnemy(const Vector4f& body, float x, float y, char type)
    : Enemy(body, x, y, REGEN_ENEMY_MAX_HP, REGEN_ENEMY_SPEED, true, REGEN_ENEMY_VALUE, type, T_REGEN_ENEMY) {

}