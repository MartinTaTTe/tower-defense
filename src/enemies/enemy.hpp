#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum TypesOfEnemies : int8_t {
    Normal,
    Multiple,
    Spawn,
    Air
};

class Enemy {
public:
    Enemy(float max_hp, float x, float y, float speed, float delay, int size,
          TypesOfEnemies type = Normal);

          //Lägg hit SetHp, GetHp, IsLand(bool, true om på land, false om i luften) funktioner h. Sandra

private:
    float               hp_;
    const float         max_hp_;
    float               x_cord_;
    float               y_cord_;
    float               speed_;
    float               delay_;
    int                 size_;
    TypesOfEnemies      type_;
};

