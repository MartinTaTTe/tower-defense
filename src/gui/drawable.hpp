#pragma once

#include <SFML/Graphics.hpp>

struct Vector2 {
    float x, y;
};

struct Vector4 {
    union {
        struct {
            float upper_left_x, upper_left_y, lower_right_x, lower_right_y;
        };
        struct {
            Vector2 upper_left, lower_right;
        };
    };
};

class Drawable {
public:
    Drawable(const Vector4& body, const std::string& texturePath);
    ~Drawable();
    void Draw(sf::RenderWindow& window) const;
    void SetSize(float width, float height);
    void SetPosition(float x, float y);
    void SetCorners(float upper_left_x, float upper_left_y, float lower_right_x, float lower_right_y);
private:
    sf::RectangleShape body_;
};
