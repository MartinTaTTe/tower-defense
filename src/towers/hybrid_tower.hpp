//A tower that can shoot all kinds of enemies

#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Hybrid_Tower : public Tower{
    public:
        Hybrid_Tower(const Vector4f& vector, int x, int y);
        void Upgrade();
};