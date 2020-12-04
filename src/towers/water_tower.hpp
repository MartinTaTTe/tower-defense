//A tower that can be placed in water
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Water_Tower : public Tower{
    public:
        Water_Tower(const Vector4f& vector, int x, int y, int price, float damage, float speed, float range, int enemy_type = 1, bool tile_type = false,  const std::string& texturePath = T_WATER_TOWER);
        void Upgrade();
};