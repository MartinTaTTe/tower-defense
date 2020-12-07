#include "enemy.hpp"
#include <iostream>

Enemy::Enemy(const Vector4f& body, float x, float y, float max_hp, float speed, bool ground, const std::string& texturePath)
    : Drawable(body, texturePath),
    x_(x),
    y_(y),
    hp_(max_hp),
    max_hp_(max_hp),
    speed_(speed),
    is_ground_(ground),
    currentTile(0) {

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
    if (hp_ <= 0) {
        event.type = EventType::Dead;
    }
    x_ += d_x_ * speed_;
    y_ += d_y_ * speed_;
    Move(d_x_ * speed_*tile_width, d_y_ * speed_*tile_height);
    return event;
}
