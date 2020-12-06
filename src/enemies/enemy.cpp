#include "enemy.hpp"
#include <iostream>

Enemy::Enemy(const Vector4i& body, float x, float y, float max_hp, float speed, bool ground, const std::string& texturePath)
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

Event Enemy::Update(float damage, float d_x_, float d_y_) {
    Event event;
    hp_ -= damage;
    if (hp_ <= 0) {
        event.type = EventType::Dead;
    }
    std::cout << "Update  " << d_x_ << ", " << d_y_ << std::endl;
    x_ += d_x_ * speed_;
    y_ += d_y_ * speed_;
    std::cout << "Updated " << x_ << ", " << y_ << std::endl;
    Move(d_x_ * speed_, d_y_ * speed_);
    return event;
}
