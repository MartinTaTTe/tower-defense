#pragma once 
/*
A Drawable that reacts to user input.
*/
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
    void Highlight(bool highlight) override;
    void Disable(bool disable) override;
    bool IsPressed() const;
    bool IsToggled() const;
    bool HasTexture() const;
private:
    bool isPressed_;
    bool isToggled_;
    bool isDisabled_;
    bool hasTexture_;
};
