// A basic tower that shoots enemies within its range

#include "towers.hpp"

class Basic_Tower : public Tower{
    public:
        Basic_Tower(int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texturePath = "basic_tower.png");
        void Upgrade();
};