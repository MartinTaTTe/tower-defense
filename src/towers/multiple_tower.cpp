#include "multiple_tower.hpp"

Multiple_Tower::Multiple_Tower(const Vector4f& vector, int x, int y):
    Tower( vector, x, y, MULTIPLE_TOWER_PRICE, MULTIPLE_TOWER_DAMAGE, MULTIPLE_TOWER_SPEED, MULTIPLE_TOWER_RANGE, MULTIPLE_TOWER_ENEMYTYPE, MULTIPLE_TOWER_TILETYPE, T_MULTIPLE_TOWER){
        upgrade_max_ = UPGRADE_MAX; // Kan laga mera upgrades om vi vill ha!
        upgrade_price_ = UPGRADE_PRICE;
}

void Multiple_Tower::Upgrade(){
    if(upgrade_ < upgrade_max_){
        upgrade_ += 1;
        if(upgrade_ == 2){
            damage_ += 2;
            upgrade_price_ += UPGRADE_PRICE;
            speed_ += 2;
        } else if(upgrade_ = 3){
            damage_ += 3;
            upgrade_price_ += UPGRADE_PRICE;
            speed_ += 3;
        }
    }
}



void Multiple_Tower::Update(std::vector<Enemy*>& enemies){
    if(targetVector_.empty()){
        for(auto enemy: enemies){
            if(((enemy->GetX() - x_)*(enemy->GetX() - x_) + (enemy->GetY() - y_)*(enemy->GetY() - y_)) <= range_*range_){
                if( enemy->IsLand() && (enemy_type_ == 1 || enemy_type_ == 3)){
                    targetVector_.push_back(enemy);
                }else if(!enemy->IsLand() && enemy_type_ == 2){
                    targetVector_.push_back(enemy);
                }
            }
    }
    }else{
        for(int i = 0; i < targetVector_.size(); i++){
            Attack(targetVector_[i]);
            if(((targetVector_[i]->GetX() - x_)*(targetVector_[i]->GetX() - x_) + (targetVector_[i]->GetY() - y_)*(targetVector_[i]->GetY() - y_)) > range_*range_){
                targetVector_.erase(targetVector_.begin() + i);
        }
        if(targetVector_.empty()){
            Update(enemies); //Rätt ställe?
        }  
    }

}