// A basic tower that shoots enemies within its range
#pragma once
#include "towers.hpp"
#include "utils/app_constants.hpp"

class Basic_Tower : public Tower{
    public:
        Basic_Tower( const Vector4f& vector, int x, int y);
        void Upgrade();
};