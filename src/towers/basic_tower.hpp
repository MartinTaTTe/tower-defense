// A basic tower that shoots enemies within its range
#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class BasicTower : public Tower{
    public:
        BasicTower(const Vector4f& vector, int x, int y);
        void Upgrade();
};