#include "enemy.hpp"
#include "../utils/texture_manager.hpp"

Enemy::Enemy(const Vector4i& body, float max_hp, float x, float y, float speed, bool ground, const std::string& texturePath)
    : Drawable(body, texturePath),
    hp_(max_hp),
    max_hp_(max_hp),
    x_(x),
    y_(y),
    speed_(speed),
    is_ground_(ground) {

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
    float move_x_ = d_x_ * speed_;
    float move_y_ = d_y_ * speed_;
    hp_ = hp_ - damage;
    if (hp_ <= 0) {
        event.type = EventType::Dead;
    }
    Move(move_x_, move_y_);
    return event;
}
