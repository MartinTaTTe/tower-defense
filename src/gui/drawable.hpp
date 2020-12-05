#pragma once
/*
Base class.
Everything that is visible to the player inherits Drawable either directly or indirectly.
*/
#include <SFML/Graphics.hpp>

struct Vector2i;
struct Vector4i;
struct Vector2f;
struct Vector4f;

class Drawable {
public:
    Drawable(const Vector4i& body, const std::string& texturePath); // body is screen coordinates
    ~Drawable();
    void            Draw(sf::RenderWindow& window) const;
    virtual void    Highlight(bool highlight);
    virtual void    Disable(bool disable);
    void            Move(float d_x, float d_y);
protected:
    sf::RectangleShape body_;
};

// Vector structs
struct Vector2i {
    int x, y;
};

struct Vector4i {
    union {
        struct {
            int upper_left_x, upper_left_y, lower_right_x, lower_right_y;
        };
        struct {
            Vector2i upper_left, lower_right;
        };
    };
};

struct Vector2f {
    float x, y;
};

struct Vector4f {
    union {
        struct {
            float upper_left_x, upper_left_y, lower_right_x, lower_right_y;
        };
        struct {
            Vector2f upper_left, lower_right;
        };
    };
};
