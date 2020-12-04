//A tower that can generate money over time or improve towers that are nearby 
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Utility_Tower : public Tower{
    public:
        Utility_Tower(const Vector4f& vector, int x, int y, int price, float damage, float speed, float range, int enemy_type = 4, bool tile_type = true, const std::string& texturePath = T_UTILITY_TOWER);
        void Upgrade();
};