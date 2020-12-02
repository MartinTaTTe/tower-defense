#include "button.hpp"
#include "../game/texture_manager.hpp"
#include "../utils/app_constants.hpp"

Button::Button(const Vector4i& body)
    : Drawable(body, T_DEFAULT_BUTTON), hasTexture_(false) {

}

Button::Button(const Vector4i& body, const std::string& texturePath)
    : Drawable(body, texturePath), hasTexture_(true) {
    
}

Button::Button(const Vector4f& body)
    : Drawable(body, T_DEFAULT_BUTTON), hasTexture_(false) {

}

Button::Button(const Vector4f& body, const std::string& texturePath)
    : Drawable(body, texturePath), hasTexture_(true) {

}

Button::~Button() {
    
}

void Button::Press(bool press) {
    if (!isDisabled_)
        isPressed_ = press;
}

void Button::Toggle() {
    if (!isDisabled_)
        isToggled_ = !isToggled_;
}

void Button::Highlight(bool highlight) {
    if (!isDisabled_)
        body_.setFillColor(sf::Color(255, 255, 255, HIGHLIGHT * highlight));
}

void Button::Disable(bool disable) {
    body_.setFillColor(sf::Color(0, 0, 0, DISABLE * disable));
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
