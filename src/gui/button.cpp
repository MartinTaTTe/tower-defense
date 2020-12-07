#include "button.hpp"

Button::Button(const Vector4f& body, const std::string& texturePath, const Event& action)
    : Drawable(body, texturePath), action_(action) {

}

Button::~Button() {
    
}

const Event Button::Press() {
    if (!isDisabled_)
        return action_;
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
