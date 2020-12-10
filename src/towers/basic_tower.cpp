#include "basic_tower.hpp"

BasicTower::BasicTower(const Vector4f& vector, int x, int y)
    :
    Tower(vector, x, y,
    BASIC_TOWER_DAMAGE,
    BASIC_TOWER_RANGE,
    false, true, true,
    T_BASIC_TOWER) {
}
void BasicTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + BASIC_TOWER_DAMAGE;
    }
}
