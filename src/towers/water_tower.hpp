//A tower that can be placed in water
#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class WaterTower : public Tower{
    public:
        WaterTower(const Vector4f& vector, int x, int y);
        void Upgrade();
};