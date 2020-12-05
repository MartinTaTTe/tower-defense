#pragma once
#include <vector>
#include <string>
#include "../gui/drawable.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"

class Enemy : public Drawable {
public:
    Enemy(
        const Vector4i& body,
        float max_hp,
        float x,
        float y,
        float speed,
        bool ground,
        const std::string& texturePath = T_DEFAULT_ENEMY
    );
    bool                IsGround() const;
    float               GetX();
    float               GetY();
    virtual Event       Update(float damage, float d_x_, float d_y_);
private:
    float               hp_;
    const float         max_hp_;
    float               x_;
    float               y_;
    float               speed_;
    int                 size_;
    bool                is_ground_;
};
