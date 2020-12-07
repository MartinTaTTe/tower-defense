#include "towers.hpp"
#include "../utils/texture_manager.hpp"


Tower::Tower(
    const Vector4i& vector,
    int x, int y,
    float damage,
    float range,
    bool can_attack_air,
    bool can_attack_ground,
    bool ground,
    const std::string& texturePath
):
x_(x),
y_(y),
damage_(damage), 
range_(range),
can_attack_air_(can_attack_air),
can_attack_ground_(can_attack_ground),
ground_(ground),
Button(vector, texturePath) {

    radius_.setRadius(range);
    radius_.setFillColor(sf::Color::Transparent);
    radius_.setOutlineThickness(10);
    radius_.setOutlineColor(sf::Color::Red);
}

Event Tower::Update(const Enemies& enemies, Event event){
    Event return_event;
    if(target_ == nullptr){
        for(auto enemy: enemies){
            if(((enemy.second->GetX() - x_)*(enemy.second->GetX() - x_) + (enemy.second->GetY() - y_)*(enemy.second->GetY() - y_)) <= range_*range_){
                if( enemy.second->IsGround() && can_attack_ground_){
                    target_ = enemy.second;
                }else if(!enemy.second->IsGround() && can_attack_air_){
                    target_ = enemy.second;
                }
                break;
            }
        }
        return_event.type = EventType::DamageEnemy;
        return_event.damage = damage_;
        return_event.enemy = target_;
    }else{
        if(((target_->GetX() - x_)*(target_->GetX() - x_) + (target_->GetY() - y_)*(target_->GetY() - y_)) > range_*range_)
            target_ = nullptr;
    }
    return return_event;
}

void Tower::Upgrade() {
    
}
