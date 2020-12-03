#include "enemy.hpp"
#include "../game/texture_manager.hpp"

Enemy::Enemy(float max_hp, float speed, float x, float y, float size,
             float delay, bool ground, TypesOfEnemies type)
    : hp_(max_hp),
      max_hp_(max_hp),
      x_(x),
      y_(y),
      speed_(speed),
      delay_(delay),
      size_(size),
      ground_(ground),
      type_(type) { }

float Enemy::GetHp() const { 
    return hp_; 
}

float Enemy::GetMaxHp() const { 
    return max_hp_; 
}

float Enemy::GetSpeed() const { 
    return speed_; 
}

float Enemy::GetDelay() const { 
    return delay_; 
}

sf::Sprite* Tower::GetSprite(){
    return &sprite_;
}

const std::pair<float, float> Enemy::GetPosition() const { 
    return {x_, y_}; 
}

const std::pair<int, int> Enemy::GetTile() const { 
    return {int(x_), int(y_)}; 
}

bool Enemy::IsAlive() const { 
    return hp_ > 0; 
}

bool Enemy::IsLand() const { 
    return ground_; 
}

TypesOfEnemies Enemy::GetType() const { 
    return type_; 
}