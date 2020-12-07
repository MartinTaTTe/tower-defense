#pragma once

#include "../enemies/enemy.hpp"
#include "../gui/button.hpp"
#include <vector>

typedef std::vector<std::pair<Vector4f, Enemy*>> Enemies;

class Tower: public Button {
public:
    Tower(
        const Vector4i& vector,
        int x, int y,
        float damage,
        float range,
        bool can_attack_air,
        bool can_attack_ground,
        bool ground,
        const std::string& texturePath = T_DEFAULT_TOWER
    ); 

    int                 GetPrice() const;
    virtual Event       Update(const Enemies& enemies, Event event);
    virtual void        Upgrade();
    virtual             ~Tower(){};
protected:
    int                 x_;
    int                 y_;
    int                 max_level_;
    int                 level_;
    float               range_;
    float               damage_;
    int                 upgrade_price_;
    bool                can_attack_air_;
    bool                can_attack_ground_;
    bool                ground_; //vilken sort av "underlag" -> true = ground, false = water
    Enemy*              target_;
    sf::CircleShape     radius_;
};









    
