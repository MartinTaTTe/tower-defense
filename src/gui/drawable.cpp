#include "drawable.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

Drawable::Drawable(const Vector4f& body, const std::string& texturePath)
    : body_({(body.lower_right_x - body.upper_left_x) * WINDOW_WIDTH, (body.lower_right_y - body.upper_left_y) * WINDOW_HEIGHT}) {
    body_.setTexture(&GetTexture(texturePath));
    body_.setPosition({body.upper_left_x * WINDOW_WIDTH, body.upper_left_y * WINDOW_HEIGHT});
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

void Drawable::Move(float d_x, float d_y) {
    auto current_pos = body_.getPosition();
    body_.setPosition({current_pos.x + d_x * WINDOW_WIDTH, current_pos.y + d_y * WINDOW_HEIGHT});
}

void Drawable::UpdateTexture(const std::string& texturePath) {
    body_.setTexture(&GetTexture(texturePath));
}

void Drawable::SetSize(const Vector2f& size) {
    body_.setSize({size.x, size.y});
}
