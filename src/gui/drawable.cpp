#include "drawable.hpp"
#include "../game/texture_manager.hpp"

Drawable::Drawable(const Vector4& body, const std::string& texturePath)
    : body_(sf::Vector2f(body.lower_right_x - body.upper_left_x, body.lower_right_y - body.upper_left_y)) {
    body_.setTexture(&GetTexture(texturePath));
}

Drawable::Drawable(const std::string& texturePath)
    : Drawable({0, 0, 0, 0}, texturePath) {

}

Drawable::~Drawable() {

}

void Drawable::Draw(sf::RenderWindow& window) const {
    window.draw(body_);
}

void Drawable::SetSize(float width, float height) {
    body_.setSize(sf::Vector2f(width, height));
}

void Drawable::SetSize(int width, int height) {
    SetSize((float)width, (float)height);
}

void Drawable::SetPosition(int x, int y) {
    body_.setPosition(x, y);
}

void Drawable::SetPosition(const Vector2& pos) {
    body_.setPosition(pos.x, pos.y);
}

void Drawable::SetCorners(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y) {
    SetPosition(upper_left_x, upper_left_y);
    SetSize(lower_right_x - upper_left_x, lower_right_y - upper_left_y);
}

void Drawable::SetCorners(const Vector2& upper_left, const Vector2& lower_right) {
    SetCorners(upper_left.x, upper_left.y, lower_right.x, lower_right.y);
}

void Drawable::SetCorners(const Vector4& corners) {
    SetCorners(corners.upper_left, corners.lower_right);
}
