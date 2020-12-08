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
    Drawable(const Vector4f& body, const std::string& texturePath); // body is realtive coordinates (0-1)
    ~Drawable();
    void            Draw(sf::RenderWindow& window) const;
    virtual void    Highlight(bool highlight);
    virtual void    Disable(bool disable);
    void            Move(float d_x, float d_y);
    void            UpdateTexture(const std::string& texturePath);
    void            SetSize(const Vector2f& size);
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

    // Use only for creating relative position, not multiplication. Containing body before.
    Vector4f operator*(const Vector4f& other) {
        return {
            (lower_right_x - upper_left_x) * other.upper_left_x  + upper_left_x,
            (lower_right_y - upper_left_y) * other.upper_left_y  + upper_left_y,
            (lower_right_x - upper_left_x) * other.lower_right_x + upper_left_x,
            (lower_right_y - upper_left_y) * other.lower_right_y + upper_left_y
        };
    }

    // Use only for creating relative position, not multiplication.
    Vector2f operator*(const Vector2f& other) {
        return {
            (lower_right_x - upper_left_x)  * other.x + upper_left_x,
            (lower_right_y - upper_left_y)  * other.y + upper_left_y
        };
    }

    // Use only for creating relative position, not division.
    Vector2f operator/(const Vector2f& other) {
        return {
            (other.x - upper_left_x) / (lower_right_x - upper_left_x),
            (other.y - upper_left_y) / (lower_right_y - upper_left_y)
        };
    }
};
