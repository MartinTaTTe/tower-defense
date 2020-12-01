#include "basic_tower.hpp"

Basic_Tower::Basic_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texturePath):
Tower(price, damage, x_coord, y_coord, size, speed, range, texturePath){
    upgrade_max_ = 3; // Kan laga mera upgrades om vi vill ha!
    upgrade_price_ = UPGRADE_PRICE;
}
void Basic_Tower::Upgrade(){
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