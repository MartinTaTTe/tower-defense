#pragma once 

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

typedef std::pair<int, int> Coords;

class Button : public Drawable {
public:
    Button(const Vector4i& body);
    Button(const Vector4i& body, const std::string& texturePath);
    Button(const Vector4f& body);
    Button(const Vector4f& body, const std::string& texturePath);
    ~Button();
    void Press(bool press);
    void Toggle();
    inline bool IsPressed() const;
    inline bool IsToggled() const;
    inline bool HasTexture() const;
private:
    bool isPressed_;
    bool isToggled_;
    bool hasTexture_;
};
