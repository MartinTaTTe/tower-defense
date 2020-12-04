#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../gui/drawable.hpp"

enum TypesOfEnemies : int8_t {
    Normal,
    Multiple,
    Spawn,
    Air
};

class Enemy : public Drawble {
public:
    Enemy(float max_hp, float x, float y, float speed, float delay, bool ground, int size,
          TypesOfEnemies type = Normal);

          //Lägg hit SetHp, GetHp, IsLand(bool, true om på land, false om i luften) funktioner h. Sandra
    void                SetHp(float hp);
    float               GetHp() const;
    float               GetMaxHp() const;
    float               GetSpeed() const;
    float               GetDelay() const;
    sf::Sprite*         GetSprite();
    const std::pair<float, float> GetPosition() const;
    const std::pair<int, int> GetTile() const;
    TypesOfEnemies      GetEnemyType() const;
    bool                IsLand() const;
    bool                IsAlive() const;
    int                 GetX();
    int                 GetY();
    //Gör en Update funktion som får damage som parameter o tar bort den mängden hp

private:
    float               hp_;
    const float         max_hp_;
    float               x_cord_;
    float               y_cord_;
    float               speed_;
    float               delay_;
    int                 size_;
    bool                ground_;
    TypesOfEnemies      type_;
};

