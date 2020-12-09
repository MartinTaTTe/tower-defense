#pragma once

#include "../gui/drawable.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"

class Enemy : public Drawable {
public:
    Enemy(
        const Vector4f& body,
        float x,
        float y,
        float max_hp,
        float speed,
        bool ground,
        int value,
        const std::string& texturePath = T_DEFAULT_ENEMY
    );
    bool                IsGround() const;
    float               GetX();
    float               GetY();
    virtual Event       Update(float damage, float d_x_, float d_y_, float tile_width, float tile_height);
    void                DrawHP(sf::RenderWindow& window);
    int                 GetValue();
    int                 currentTile;
protected:
    float               hp_;
    const float         max_hp_;
    float               x_;
    float               y_;
    float               speed_;
    bool                is_ground_;
    int                 value_;
    Drawable            hp_bar_;
};
