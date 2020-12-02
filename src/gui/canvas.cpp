#include "canvas.hpp"

Canvas::Canvas(sf::RectangleShape body)
    : body_(body) {
    width_  = body.getSize().x - body.getPosition().x;
    height_ = body.getSize().y - body.getPosition().y;
}

Canvas::~Canvas() {
    for (auto button : buttons_)
        delete button.second;
    for (auto drawable : drawables_)
        delete drawable.second;
}

Event Canvas::EventHandler(const Event& event) {
    Vector2f relative;
    switch (event.type)
    {
    case EventType::Resize:
        Update(event.body);
        break;
    case EventType::MouseMovement:
        relative.x = (event.coords.x - body_.getPosition().x) / width_;
        relative.y = (event.coords.y - body_.getPosition().y) / height_;
        for (auto button : buttons_) {
            if (button.first.upper_left_x < relative.x && relative.x < button.first.lower_right_x &&
                button.first.upper_left_y < relative.y && relative.y < button.first.lower_right_y)
                button.second->Highlight(true);
            else
                button.second->Highlight(false);
        }
        break;
    case EventType::MouseClick:
        relative.x = (event.coords.x - body_.getPosition().x) / width_;
        relative.y = (event.coords.y - body_.getPosition().y) / height_;
        for (auto button : buttons_) {
            if (button.first.upper_left_x < relative.x && relative.x < button.first.lower_right_x &&
                button.first.upper_left_y < relative.y && relative.y < button.first.lower_right_y)
                button.second->Press(true);
        }
        break;
    default:
        break;
    }
    return Event(EventType::None);
}

void Canvas::Update(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y) {
    body_.setPosition((float)upper_left_x, (float)upper_left_y);
    body_.setSize(sf::Vector2f((float)(lower_right_x - upper_left_x), (float)(lower_right_y - upper_left_y)));
    for (auto button : buttons_)
        button.second->SetCorners(
            upper_left_x + button.first.upper_left_x  * (lower_right_x - upper_left_x) / 100,
            upper_left_y + button.first.upper_left_y  * (lower_right_y - upper_left_y) / 100,
            upper_left_x + button.first.lower_right_x * (lower_right_x - upper_left_x) / 100,
            upper_left_y + button.first.lower_right_y * (lower_right_y - upper_left_y) / 100
        );
    for (auto drawable : drawables_)
        drawable.second->SetCorners(
            upper_left_x + drawable.first.upper_left_x  * (lower_right_x - upper_left_x) / 100,
            upper_left_y + drawable.first.upper_left_y  * (lower_right_y - upper_left_y) / 100,
            upper_left_x + drawable.first.lower_right_x * (lower_right_x - upper_left_x) / 100,
            upper_left_y + drawable.first.lower_right_y * (lower_right_y - upper_left_y) / 100
        );
}

void Canvas::Update(const Vector2i& upper_left, const Vector2i& lower_right) {
    Update(upper_left.x, upper_left.y, lower_right.x, lower_right.y);
}

void Canvas::Update(const Vector4i& corners) {
    Update(corners.upper_left_x, corners.upper_left_y, corners.lower_right_x, corners.lower_right_y);
}
    
void Canvas::Draw(sf::RenderWindow& window) {
    for (auto drawable : drawables_)
        drawable.second->Draw(window);
    for (auto button : buttons_)
        button.second->Draw(window);
}

void Canvas::AddButton(const Vector4f& position, const std::string& texturePath) {
    buttons_.push_back(std::pair<Vector4f, Button*>(position, new Button(position, texturePath)));
}

void Canvas::AddDrawable(const Vector4f& position, const std::string& texturePath) {
    drawables_.push_back(std::pair<Vector4f, Drawable*>(position, new Drawable(position, texturePath)));
}
