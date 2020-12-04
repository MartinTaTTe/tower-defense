#include "flying_tower.hpp"

Flying_Tower::Flying_Tower(const Vector4f& vector, int x, int y, int price, float damage, float speed, float range, int enemy_type,  bool tile_type, const std::string& texturePath):
Tower( vector,x, y, price, damage, speed, range, enemy_type, tile_type,  texturePath){
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