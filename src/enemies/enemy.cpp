#include "enemy.hpp"

Enemy::Enemy(const Vector4f& body, float x, float y, float max_hp, float speed, bool ground, int value, char type, const std::string& texturePath)
    : Drawable(body, texturePath),
    x_(x),
    y_(y),
    hp_(max_hp),
    max_hp_(max_hp),
    speed_(speed),
    is_ground_(ground),
    currentTile(0),
    EnemyType_(type),
    hp_bar_({
        body.upper_left_x,
        body.upper_left_y,
        body.lower_right_x,
        body.lower_right_y * HP_BAR_THICC
    }, T_HP_BAR),
    value_(value) {

}

bool Enemy::IsGround() const {
    return is_ground_;
}

float Enemy::GetX() {
    return x_;
}

float Enemy::GetY() {
    return y_;
}

Event Enemy::Update(float damage, float d_x_, float d_y_, float tile_width, float tile_height) {
    Event event;
    hp_ -= damage;
    if (EnemyType_ == 'S' && hp_ <= 0) {
        event.type = EventType::SpawnKill;
        event.position.x = x_;
        event.position.y = y_;
    } else if (hp_ <= 0) {
        event.type = EventType::Dead;
    } else if (EnemyType_ == 'R' && hp_ <= max_hp_) {
        hp_ += REGEN_ENEMY_HPREGEN;
    }
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

void Enemy::DrawHP(sf::RenderWindow& window) {
    hp_bar_.Draw(window);
}

int Enemy::GetValue() {
    return value_;
}
