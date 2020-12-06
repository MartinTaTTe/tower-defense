#include "spawn_enemy.hpp"
#include "../utils/app_constants.hpp"

SpawnEnemy::SpawnEnemy(const Vector4i& body, float x, float y)
    : Enemy(body, x, y, SPAWN_ENEMY_MAX_HP, SPAWN_ENEMY_SPEED, true) {

}