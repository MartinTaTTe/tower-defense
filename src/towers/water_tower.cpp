#include "water_tower.hpp"

Water_Tower::Water_Tower(const Vector4f& vector, int x, int y):
Tower( vector, x, y, WATER_TOWER_PRICE, WATER_TOWER_DAMAGE, WATER_TOWER_SPEED, WATER_TOWER_RANGE, WATER_TOWER_ENEMYTYPE, WATER_TOWER_TILETYPE, T_WATER_TOWER){
    upgrade_max_ = 3; // Kan laga mera upgrades om vi vill ha!
    upgrade_price_ = UPGRADE_PRICE;
}
void Water_Tower::Upgrade(){
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