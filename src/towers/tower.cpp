#include "tower.hpp"
#include "../utils/texture_manager.hpp"
#include <iostream>


Tower::Tower(
    const Vector4f& vector,
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
target_(nullptr),
line_(sf::LinesStrip, 2),
Button(vector, texturePath) {

    radius_.setRadius(range);
    radius_.setFillColor(sf::Color::Transparent);
    radius_.setOutlineThickness(10);
    radius_.setOutlineColor(sf::Color::Red);
    Vector2f realUp = {vector.upper_left_x*WINDOW_WIDTH, vector.upper_left_y*WINDOW_HEIGHT};
    Vector2f realDown = {vector.lower_right_x*WINDOW_WIDTH, vector.lower_right_y*WINDOW_HEIGHT};
    line_[0].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line_[0].color = sf::Color::Red;
    line_[1].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line_[1].color = sf::Color::Red;
}

Event Tower::Update(const Enemies& enemies, Event event, double d_time){
    Event return_event;
    return_event.damage = 0;
    if (target_ == nullptr || event.condition){
        target_ = nullptr;
        if (!can_attack_air_ && !can_attack_ground_) {
            return_event.tower_type = 'U';
            return_event.damage = UTILITY_TOWER_DAMAGE*d_time;
            return_event.type = EventType::AddGold;
            return return_event;
        }
        for(auto enemy: enemies){
            if(((enemy.second->GetX() - x_)*(enemy.second->GetX() - x_) + (enemy.second->GetY() - y_)*(enemy.second->GetY() - y_)) <= range_*range_){
                if ((enemy.second->IsGround() && can_attack_ground_) ||
                    (!enemy.second->IsGround() && can_attack_air_)) {
                    target_ = enemy.second;
                    break;
                }
            }
        }
    }else{
        target_->Update(damage_ * d_time, 0, 0, 0, 0);
        if(((target_->GetX() - x_)*(target_->GetX() - x_) + (target_->GetY() - y_)*(target_->GetY() - y_)) > range_*range_)
            target_ = nullptr;
    }
    return return_event;
}

void Tower::DrawLine(sf::RenderWindow& window, float tile_width, float tile_height) {
    if (target_ != nullptr) {
        float xMult = tile_width*WINDOW_WIDTH*MAP_WIDTH;
        float yMult = tile_height*WINDOW_HEIGHT*MAP_HEIGHT;
        line_[1].position = sf::Vector2f(target_->GetX()*xMult + xMult/2, target_->GetY()*yMult + yMult/2);
        window.draw(line_);
    }
}
