#include "canvas.hpp"

Canvas::Canvas(sf::RectangleShape body)
    : body_(body) {
        body.getPosition();
}

Canvas::~Canvas() {
    for (auto button : buttons_)
        delete button;
}

void Canvas::EventHandler() {

}
    
void Canvas::Draw(sf::RenderWindow& window) {

}
