//A tower that can only shoot flying enemies
#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class FlyingTower : public Tower{
    public:
        FlyingTower(const Vector4f& vector, int x, int y);
        void Upgrade();
};