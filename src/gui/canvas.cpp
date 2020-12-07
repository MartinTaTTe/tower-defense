#include "canvas.hpp"

Canvas::Canvas(const Vector4f& body)
    : body_(body) {
    font_.loadFromFile(DEFAULT_FONT);
}

Canvas::~Canvas() {
    for (auto button : buttons_)
        delete button.second;
    for (auto drawable : drawables_)
        delete drawable.second;
    for (auto canvas : canvases_)
        delete canvas.second;
}

Event Canvas::EventHandler(const Event& event) {
    Event return_event;
    Vector2f relative = body_ / event.position;
    switch (event.type)
    {
    case EventType::MouseMovement:
        for (auto button : buttons_) {
            if (
                button.first.upper_left_x  < relative.x &&
                button.first.lower_right_x > relative.x &&
                button.first.upper_left_y  < relative.y &&
                button.first.lower_right_y > relative.y
            )
                button.second->Highlight(true);
            else
                button.second->Highlight(false);
        }
        break;
    case EventType::MouseClick:
        for (auto button : buttons_) {
            if (
                button.first.upper_left_x  < relative.x &&
                button.first.lower_right_x > relative.x &&
                button.first.upper_left_y  < relative.y &&
                button.first.lower_right_y > relative.y
            )
                return button.second->Press();
        }
        break;
    default:
        break;
    }
    return return_event;
}

void Canvas::Draw(sf::RenderWindow& window) const {
    for (auto drawable : drawables_)
        drawable.second->Draw(window);
    for (auto button : buttons_)
        button.second->Draw(window);
    CustomDraw(window);
    for (auto text : texts_) {
        text.second.setFont(font_);
        window.draw(text.second);
    }
    for (auto canvas : canvases_)
        canvas.second->Draw(window);
}

void Canvas::CustomDraw(sf::RenderWindow& window) const {
    
}

void Canvas::AddButton(const Vector4f& position, const std::string& texturePath, const Event& action) {
    buttons_.push_back(
        std::pair<Vector4f, Button*>
        (position, new Button(body_ * position, texturePath, action))
    );
}

void Canvas::AddDrawable(const Vector4f& position, const std::string& texturePath) {
    drawables_.push_back(
        std::pair<Vector4f, Drawable*>
        (position, new Drawable(body_ * position, texturePath))
    );
}

void Canvas::AddCanvas(const Vector4f& position) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position, new Canvas(body_ * position))
    );
}

void Canvas::AddText(const Vector2f& position, const std::string& string, int font_size, sf::Color color) {
    sf::Text text;
    text.setString(string);
    text.setFont(font_);
    text.setCharacterSize(font_size);
    text.setPosition({
        ((body_.lower_right_x - body_.upper_left_x) * position.x + body_.upper_left_x) * WINDOW_WIDTH,
        ((body_.lower_right_y - body_.upper_left_y) * position.y + body_.upper_left_y) * WINDOW_HEIGHT
    });
    text.setFillColor(color);
    texts_.push_back(
        std::pair<Vector2f, sf::Text>
        (position, text)
    );
}

void Canvas::UpdateString(int i, const std::string& string) {
    texts_[i].second.setString(string);
}
