#include "drawable.hpp"
#include "../game/texture_manager.hpp"

Drawable::Drawable(const Vector4& body, const std::string& texturePath)
    : body_(sf::Vector2f(body.lower_right_x - body.upper_left_x, body.lower_right_y - body.upper_left_y)) {
    body_.setTexture(&GetTexture(texturePath));
}

Drawable::~Drawable() {

}

void Drawable::Draw(sf::RenderWindow& window) const {
    window.draw(body_);
}

void Drawable::SetSize(float width, float height) {
    body_.setSize(sf::Vector2f(width, height));
}

void Drawable::SetPosition(float x, float y) {
    body_.setPosition(x, y);
}

void Drawable::SetCorners(float upper_left_x, float upper_left_y, float lower_right_x, float lower_right_y) {
    SetPosition(upper_left_x, upper_left_y);
    SetSize(lower_right_x - upper_left_x, lower_right_y - upper_left_y);
}
