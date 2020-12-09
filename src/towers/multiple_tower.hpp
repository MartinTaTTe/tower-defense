//A tower that can attack multiple enemies at the same time

#pragma once
#include "towers.hpp"
#include "../utils/app_constants.hpp"

class Multiple_Tower : public Tower{
    public:
        Multiple_Tower(const Vector4f& vector, int x, int y);
        void Upgrade();
        //void Update(std::vector<Enemy*>& enemies) override;

    private:
        std::vector<Enemy*> targetVector_;
};