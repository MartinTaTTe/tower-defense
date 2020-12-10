#include "water_tower.hpp"

WaterTower::WaterTower(const Vector4f& vector, int x, int y)
    :
    Tower(vector, x, y,
    WATER_TOWER_DAMAGE,
    WATER_TOWER_RANGE,
    false, true, false,
    T_WATER_TOWER) {
}
void WaterTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + WATER_TOWER_DAMAGE;
    }


}