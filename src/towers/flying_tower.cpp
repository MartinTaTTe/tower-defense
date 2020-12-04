#include "flying_tower.hpp"

Flying_Tower::Flying_Tower(const Vector4f& vector, int x, int y):
Tower( vector,x, y, FLYING_TOWER_PRICE, FLYING_TOWER_DAMAGE, FLYING_TOWER_SPEED, FLYING_TOWER_RANGE, FLYING_TOWER_ENEMYTYPE, FLYING_TOWER_TILETYPE, T_FLYING_TOWER){
    upgrade_max_ = 3; // Kan laga mera upgrades om vi vill ha!
    upgrade_price_ = UPGRADE_PRICE;
}
void Flying_Tower::Upgrade(){
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