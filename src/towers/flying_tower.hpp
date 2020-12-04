//A tower that can only shoot flying enemies
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Flying_Tower : public Tower{
    public:
        Flying_Tower(const Vector4f& vector, int x, int y);
        void Upgrade();
};