//A tower that can attack multiple enemies at the same time

#pragma once
#include "tower.hpp"
#include "../utils/app_constants.hpp"

class MultipleTower : public Tower{
public:
    MultipleTower(const Vector4f& vector, int x, int y);
    void  Upgrade();
    Event Update(const Enemies& enemies, Event event, double d_time) override;
    void  DrawLine(sf::RenderWindow& window, float tile_width, float tile_height) override;
private:
    std::vector<Enemy*> targetVector_;
    int                 maxTargets_;
    sf::VertexArray     line1_;
    sf::VertexArray     line2_;
};