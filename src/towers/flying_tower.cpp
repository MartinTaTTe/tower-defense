#include "flying_tower.hpp"

FlyingTower::FlyingTower(const Vector4f& vector, int x, int y)
    :
    Tower(vector, x, y,
    FLYING_TOWER_DAMAGE,
    FLYING_TOWER_RANGE,
    true, false, true,
    T_FLYING_TOWER) {
}
void FlyingTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + FLYING_TOWER_DAMAGE;
    }


}