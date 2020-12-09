#include "hybrid_tower.hpp"

HybridTower::HybridTower(const Vector4f& vector, int x, int y)
    :
    Tower(vector, x, y,
    HYBRID_TOWER_DAMAGE,
    HYBRID_TOWER_RANGE,
    true, true, true,
    T_HYBRID_TOWER) {
    upgrade_price_ = UPGRADE_PRICE;
}

void HybridTower::Upgrade(){
    if(level_ < max_level_){
        level_++;
        range_++;
        damage_ + HYBRID_TOWER_DAMAGE;
    }
}

