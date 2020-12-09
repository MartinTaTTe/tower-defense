#include "spawn_enemy.hpp"
#include "../utils/app_constants.hpp"

SpawnEnemy::SpawnEnemy(const Vector4f& body, float x, float y, char type)
    : Enemy(body, x, y, SPAWN_ENEMY_MAX_HP, SPAWN_ENEMY_SPEED, true, SPAWN_ENEMY_VALUE, type, T_SPAWN_ENEMY) {

}