#pragma once
/*
Everything that is visible to the player inherits Drawable either directly or indirectly.
*/
#include <SFML/Graphics.hpp>

struct Vector2i;
struct Vector4i;
struct Vector2f;
struct Vector4f;

class Drawable {
public:
    Drawable(const Vector4i& body, const std::string& texturePath);
    Drawable(const Vector4f& body, const std::string& texturePath);
    Drawable(const std::string& texturePath);
    ~Drawable();
    void            Draw(sf::RenderWindow& window) const;
    void            SetSize(float width, float height);
    void            SetSize(int width, int height);
    void            SetPosition(float x, float y);
    void            SetPosition(int x, int y);
    void            SetPosition(const Vector2i& pos);
    void            SetCorners(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y);
    void            SetCorners(const Vector2i& upper_left, const Vector2i& lower_right);
    void            SetCorners(const Vector4i& corners);
    virtual void    Highlight(bool highlight);
    virtual void    Disable(bool disable);
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
