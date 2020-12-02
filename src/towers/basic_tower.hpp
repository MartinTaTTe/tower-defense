// A basic tower that shoots enemies within its range
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Basic_Tower : public Tower{
    public:
        Basic_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type = 1, bool tile_type = true, const std::string& texturePath = "basic_tower.png");
        void Upgrade();
};