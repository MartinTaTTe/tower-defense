#include "drawable.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

Drawable::Drawable(const Vector4f& body, const std::string& texturePath)
    : body_(sf::Vector2f(body.lower_right_x - body.upper_left_x, body.lower_right_y - body.upper_left_y)) {
    body_.setTexture(&GetTexture(texturePath));
    body_.setPosition(sf::Vector2f(body.upper_left_x, body.upper_left_y));
}

Drawable::Drawable(const std::string& texturePath)
    : Drawable(Vector4f({0, 0, 0, 0}), texturePath) {

}

Drawable::~Drawable() {

}

void Drawable::Draw(sf::RenderWindow& window) const {
    window.draw(body_);
}

void Drawable::Highlight(bool highlight) {
    body_.setFillColor(sf::Color(255, 255, 255, 255 - HIGHLIGHT * highlight));
}

void Drawable::Disable(bool disable) {
    body_.setFillColor(sf::Color(255 - DISABLE * disable, 255 - DISABLE * disable, 255 - DISABLE * disable, 255));
}
