//A tower that can generate money over time or improve towers that are nearby 
#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class UtilityTower : public Tower{
    public:
        UtilityTower(const Vector4f& vector, int x, int y);
        void Upgrade();
};