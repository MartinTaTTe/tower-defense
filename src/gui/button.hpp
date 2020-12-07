#pragma once 
/*
A Drawable that reacts to user input.
*/
#include "drawable.hpp"
#include "../utils/event.hpp"
#include "../utils/app_constants.hpp"

class Button : public Drawable {
public:
    Button(const Vector4f& body, const std::string& texturePath = T_DEFAULT_BUTTON, const Event& action = Event());
    ~Button();
    const Event Press();
    void        Highlight(bool highlight) override;
    void        Disable(bool disable) override;
private:
    bool  isDisabled_;
    Event action_;
};
