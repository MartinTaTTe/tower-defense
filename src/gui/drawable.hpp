#pragma once

#include <SFML/Graphics.hpp>

struct Vector2 {
    int x, y;
};

struct Vector4 {
    union {
        struct {
            int upper_left_x, upper_left_y, lower_right_x, lower_right_y;
        };
        struct {
            Vector2 upper_left, lower_right;
        };
    };
};

class Drawable {
public:
    Drawable(const Vector4& body, const std::string& texturePath);
    Drawable(const std::string& texturePath);
    ~Drawable();
    void                Draw(sf::RenderWindow& window) const;
    void                SetSize(float width, float height);
    void                SetSize(int width, int height);
    void                SetPosition(int x, int y);
    void                SetPosition(const Vector2& pos);
    void                SetCorners(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y);
    void                SetCorners(const Vector2& upper_left, const Vector2& lower_right);
    void                SetCorners(const Vector4& corners);
private:
    sf::RectangleShape  body_;
};
