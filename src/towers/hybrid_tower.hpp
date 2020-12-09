//A tower that can shoot all kinds of enemies

#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class HybridTower : public Tower{
    public:
        HybridTower(const Vector4f& vector, int x, int y);
        void Upgrade();
};