//A tower that can generate money over time or improve towers that are nearby 
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Utility_Tower : public Tower{
    public:
        Utility_Tower(const Vector4f& vector, int x, int y);
        void Upgrade();
};