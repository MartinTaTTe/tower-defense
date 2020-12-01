#include "basic_tower.hpp"

Basic_Tower::Basic_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texturePath):
Tower(price, damage, x_coord, y_coord, size, speed, range, texturePath){
    upgrade_max_ = 5;
    upgrade_price_ = 1000;

}
void Basic_Tower::Upgrade(){
    if(upgrade_ < upgrade_max_){
        upgrade_ += 1;
        if(upgrade_ == 2){
            
        }
    }


}