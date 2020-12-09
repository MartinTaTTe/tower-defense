#include "regen_enemy.hpp"
#include "../utils/app_constants.hpp"

RegenEnemy::RegenEnemy(const Vector4f& body, float x, float y)
    : Enemy(body, x, y, REGEN_ENEMY_MAX_HP, REGEN_ENEMY_SPEED, true, REGEN_ENEMY_VALUE, T_REGEN_ENEMY) {

}

Event RegenEnemy::Update(float damage, float d_x_, float d_y_, float tile_width, float tile_height) {
    Event event;
    hp_ -= damage;
    if (hp_ <= 0) {
        event.type = EventType::Dead;
    } else if (hp_ < max_hp_)
        hp_ += REGEN_ENEMY_HPREGEN;
    hp_bar_.SetSize({
        body_.getSize().x * hp_ / max_hp_,
        body_.getSize().y * HP_BAR_THICC
    });
    x_ += d_x_ * speed_;
    y_ += d_y_ * speed_;
    Move(d_x_ * speed_*tile_width, d_y_ * speed_*tile_height);
    hp_bar_.Move(d_x_ * speed_*tile_width, d_y_ * speed_*tile_height);
    return event;
}
