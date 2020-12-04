#include "utility_tower.hpp"

Utility_Tower::Utility_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type, bool tile_type, const std::string& texturePath):
Tower(price, damage, x_coord, y_coord, size, speed, range, enemy_type, tile_type, T_UTILITY_TOWER){
    upgrade_max_ = 3; // Kan laga mera upgrades om vi vill ha!
    upgrade_price_ = UPGRADE_PRICE;
    money_from_wave_ = 250;

}
void Utility_Tower::Upgrade(){
    if(upgrade_ < upgrade_max_){
        upgrade_ += 1;
        if(upgrade_ == 2){
            money_from_wave_ += 250;
            upgrade_price_ += UPGRADE_PRICE;
        } else if(upgrade_ = 3){
            money_from_wave_ += 250;
            upgrade_price_ += UPGRADE_PRICE;
        }
    }
}