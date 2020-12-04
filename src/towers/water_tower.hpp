//A tower that can be placed in water
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Water_Tower : public Tower{
    public:
        Water_Tower(const Vector4f& vector, int x, int y);
        void Upgrade();
};