#include "hybrid_tower.hpp"

Hybrid_Tower::Hybrid_Tower(const Vector4f& vector, int x, int y):
Tower( vector, x, y, HYBRID_TOWER_PRICE, HYBRID_TOWER_DAMAGE, HYBRID_TOWER_SPEED, HYBRID_TOWER_RANGE, HYBRID_TOWER_ENEMYTYPE, HYBRID_TOWER_TILETYPE, T_HYBRID_TOWER){
    upgrade_max_ = UPGRADE_MAX; // Kan laga mera upgrades om vi vill ha!
    upgrade_price_ = UPGRADE_PRICE;
}

void Hybrid_Tower::Upgrade(){
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

