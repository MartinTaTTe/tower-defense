#pragma once 
/*
A Drawable that reacts to user input.
*/
#include "drawable.hpp"
#include "../utils/event.hpp"
#include "../utils/app_constants.hpp"

typedef std::pair<int, int> Coords;

class Button : public Drawable {
public:
    Button(const Vector4f& body, const std::string& texturePath = T_DEFAULT_BUTTON, const Event& action = Event());
    ~Button();
    const Event Press(bool press);
    const Event Toggle();
    void        Highlight(bool highlight) override;
    void        Disable(bool disable) override;
    bool        IsPressed() const;
    bool        IsToggled() const;
    bool        HasTexture() const;
private:
    bool  isPressed_;
    bool  isToggled_;
    bool  isDisabled_;
    bool  hasTexture_;
    Event action_;
};
