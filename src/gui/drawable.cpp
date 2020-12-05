#include "drawable.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

Drawable::Drawable(const Vector4i& body, const std::string& texturePath)
    : body_(sf::Vector2f((float)(body.lower_right_x - body.upper_left_x), (float)(body.lower_right_y - body.upper_left_y))) {
    body_.setTexture(&GetTexture(texturePath));
    body_.setPosition(sf::Vector2f((float)body.upper_left_x, (float)body.upper_left_y));
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

void Drawable::Move(int d_x, int d_y) {
    auto current_pos = body_.getPosition();
    body_.setPosition(sf::Vector2f((float)d_x / WINDOW_WIDTH + current_pos.x, (float)d_y / WINDOW_HEIGHT + current_pos.y));
}
