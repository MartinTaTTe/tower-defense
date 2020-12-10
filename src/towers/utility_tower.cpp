#include "utility_tower.hpp"

UtilityTower::UtilityTower(const Vector4f& vector,int x, int y)
    :
    Tower(vector, x, y,
    UTILITY_TOWER_DAMAGE,
    UTILITY_TOWER_RANGE,
    false, false, true,
    T_UTILITY_TOWER) {
}
void UtilityTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + UTILITY_TOWER_DAMAGE;
    }
}