#include "multiple_tower.hpp"
#include <iostream>

MultipleTower::MultipleTower(const Vector4f& vector, int x, int y)
    :
    Tower(vector, x, y,
    MULTIPLE_TOWER_DAMAGE,
    MULTIPLE_TOWER_RANGE,
    false, true, true,
    T_MULTIPLE_TOWER),
    maxTargets_(3),
    line1_(sf::LinesStrip, 2),
    line2_(sf::LinesStrip, 2)
    {
    Vector2f realUp = {vector.upper_left_x*WINDOW_WIDTH, vector.upper_left_y*WINDOW_HEIGHT};
    Vector2f realDown = {vector.lower_right_x*WINDOW_WIDTH, vector.lower_right_y*WINDOW_HEIGHT};
    line1_[0].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line1_[0].color = sf::Color::Red;
    line1_[1].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line1_[1].color = sf::Color::Red;
    line2_[0].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line2_[0].color = sf::Color::Red;
    line2_[1].position = sf::Vector2f(realUp.x + (realDown.x - realUp.x)/2, realUp.y + (realDown.y - realUp.y)/2);
    line2_[1].color = sf::Color::Red;
}

void MultipleTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + HYBRID_TOWER_DAMAGE;
    }
}

Event MultipleTower::Update(const Enemies& enemies, Event event, double d_time){
    Event return_event;
    return_event.increments.x = 0;
    if (targetVector_.size() < maxTargets_ || event.condition) {
        targetVector_.clear();
        for(auto enemy: enemies) {
            if (targetVector_.size() < maxTargets_ &&
                ((enemy.second->GetX() - x_)*(enemy.second->GetX() - x_) + (enemy.second->GetY() - y_)*(enemy.second->GetY() - y_)) <= range_*range_) {
                if ((enemy.second->IsGround() && can_attack_ground_) ||
                    (!enemy.second->IsGround() && can_attack_air_)) {
                    targetVector_.push_back(enemy.second);
                }
            }
        }
        for (auto enemy = targetVector_.begin(); enemy != targetVector_.end(); enemy++) {
            (*enemy)->Update(damage_ * d_time, 0, 0, 0, 0);
            if((((*enemy)->GetX() - x_)*((*enemy)->GetX() - x_) + ((*enemy)->GetY() - y_)*((*enemy)->GetY() - y_)) > range_*range_)
                enemy = targetVector_.erase(enemy);
            if (enemy == targetVector_.end()) break;
        }
    } else {
        for (auto enemy = targetVector_.begin(); enemy != targetVector_.end(); enemy++) {
            (*enemy)->Update(damage_ * d_time, 0, 0, 0, 0);
            if((((*enemy)->GetX() - x_)*((*enemy)->GetX() - x_) + ((*enemy)->GetY() - y_)*((*enemy)->GetY() - y_)) > range_*range_)
                enemy = targetVector_.erase(enemy);
            if (enemy == targetVector_.end()) break;
        }
    }
    return return_event;
}

void MultipleTower::DrawLine(sf::RenderWindow& window, float tile_width, float tile_height) {
    float xMult = tile_width*WINDOW_WIDTH*MAP_WIDTH;
    float yMult = tile_height*WINDOW_HEIGHT*MAP_HEIGHT;
    if (targetVector_.size() > 0) {
        line_[1].position = sf::Vector2f(targetVector_[0]->GetX()*xMult + xMult/2, targetVector_[0]->GetY()*yMult + yMult/2);
        window.draw(line_);
    }
    if (targetVector_.size() > 1) {
        line1_[1].position = sf::Vector2f(targetVector_[1]->GetX()*xMult + xMult/2, targetVector_[1]->GetY()*yMult + yMult/2);
        window.draw(line1_);
    }
    if (targetVector_.size() > 2) {
        line2_[1].position = sf::Vector2f(targetVector_[2]->GetX()*xMult + xMult/2, targetVector_[2]->GetY()*yMult + yMult/2);
        window.draw(line2_);
    }
}
