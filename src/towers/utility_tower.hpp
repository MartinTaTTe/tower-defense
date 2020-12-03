//A tower that can generate money over time or improve towers that are nearby 
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Utility_Tower : public Tower{
    public:
        Utility_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type = 4, bool tile_type = true, const std::string& texturePath = "utility_tower.png");
        void Upgrade();
};