//A tower that can only shoot flying enemies
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Flying_Tower : public Tower{
    public:
        Flying_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type = 2, bool tile_type = true, const std::string& texturePath = "flying_tower.png");
        void Upgrade();
};