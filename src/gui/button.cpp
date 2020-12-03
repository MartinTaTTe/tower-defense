#include "button.hpp"

Button::Button(const Vector4f& body, const std::string& texturePath, const Event& action)
    : Drawable(body, texturePath), hasTexture_(true), action_(action) {

}

Button::~Button() {
    
}

const Event Button::Press(bool press) {
    if (!isDisabled_) {
        isPressed_ = press;
        return action_;
    }
    return Event();
}

const Event Button::Toggle() {
    if (!isDisabled_)
        isToggled_ = !isToggled_;
    if (isToggled_)
        return action_;
    else
        return Event();
}

void Button::Highlight(bool highlight) {
    if (!isDisabled_)
        body_.setFillColor(sf::Color(255, 255, 255, 255 - HIGHLIGHT * highlight));
}

void Button::Disable(bool disable) {
    body_.setFillColor(sf::Color(255 - DISABLE * disable, 255 - DISABLE * disable, 255 - DISABLE * disable, 255));
    isDisabled_ = disable;
}

bool Button::IsPressed() const {
    return isPressed_;
}

bool Button::IsToggled() const {
    return isToggled_;
}

bool Button::HasTexture() const {
    return hasTexture_;
}
