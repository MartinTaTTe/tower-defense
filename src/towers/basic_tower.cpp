#include "basic_tower.hpp"

Basic_Tower::Basic_Tower( const Vector4f& vector, int x, int y):
Tower(vector, x, y, BASIC_TOWER_PRICE, BASIC_TOWER_DAMAGE, BASIC_TOWER_SPEED, BASIC_TOWER_RANGE, BASIC_TOWER_ENEMYTYPE, BASIC_TOWER_TILETYPE, T_BASIC_TOWER){
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