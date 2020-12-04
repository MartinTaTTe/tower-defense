#include "towers.hpp"
#include "../utils/texture_manager.hpp"


    Tower::Tower(const Vector4f& vector, int x, int y, int price, float damage, float speed, float range, int enemy_type, bool tile_type, const std::string& texturePath):
    x_(x),
    y_(y),
    
    price_(price), 
    damage_(damage), 
    speed_(speed),
    range_(range),
    enemy_type_(enemy_type),
    tile_type_(tile_type),
    upgrade_(1),
    money_from_wave_(0),
    target_(nullptr),
    Button(vector){

        radius_.setRadius(range);
        radius_.setFillColor(sf::Color::Transparent);
        radius_.setOutlineThickness(10);
        radius_.setOutlineColor(sf::Color::Red);
    }

    void Tower::Attack() const{
        if(target_ != nullptr) {
            target_->Update(damage_);
        }
    }
    
    int Tower::GetPrice() const{
        return price_;
    }
    float Tower::GetSpeed() const{
        return speed_;
    }
    int Tower::GetUpgrade() const{
        return upgrade_;
    }
    float Tower::GetRange(){
        return range_;
    }
    int Tower:: MoneyFromWave() const{
        return money_from_wave_;
    }
    bool Tower::CanBeUpgraded() const{
        return upgrade_ < upgrade_max_;
    }
    void Tower::Update(std::vector<Enemy*>& enemies){
        if(target_ == nullptr){
            for(auto enemy: enemies){
                if(((enemy->GetX() - x_)*(enemy->GetX() - x_) + (enemy->GetY() - y_)*(enemy->GetY() - y_)) <= range_*range_){
                    if( enemy->IsLand() && (enemy_type_ == 1 || enemy_type_ == 3)){
                        target_ = enemy;
                    }else if(!enemy->IsLand() && enemy_type_ == 2){
                        target_ = enemy;
                    }
                    break;
                }
            }
        }else{
            Attack();
            if(((target_->GetX() - x_)*(target_->GetX() - x_) + (target_->GetY() - y_)*(target_->GetY() - y_)) > range_*range_){
                    target_ = nullptr;
                    Update(enemies);
        }
    }