#include "canvas.hpp"
#include "iostream"

Canvas::Canvas(sf::RectangleShape body)
    : body_(body) {
}

Canvas::Canvas(const Vector4f& body) {
    width_  = body.lower_right_x - body.upper_left_x;
    height_ = body.lower_right_y - body.upper_left_y;
    body_.setPosition(sf::Vector2f(body.upper_left_x, body.upper_left_y));
    body_.setSize(sf::Vector2f(width_, height_));
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
        Update({
            (float)event.body.upper_left_x,
            (float)event.body.upper_left_y,
            (float)event.body.lower_right_x,
            (float)event.body.lower_right_y
        });
        break;
    case EventType::MouseMovement:
        relative.x = (event.coords.x - body_.getPosition().x) / width_  * 100;
        relative.y = (event.coords.y - body_.getPosition().y) / height_ * 100;
        for (auto button : buttons_) {
            if (button.first.upper_left_x < relative.x && relative.x < button.first.lower_right_x &&
                button.first.upper_left_y < relative.y && relative.y < button.first.lower_right_y)
                button.second->Highlight(true);
            else
                button.second->Highlight(false);
        }
        break;
    case EventType::MouseClick:
        relative.x = (event.coords.x - body_.getPosition().x) / width_  * 100;
        relative.y = (event.coords.y - body_.getPosition().y) / height_ * 100;
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
    width_  = lower_right_x - upper_left_x;
    height_ = lower_right_y - upper_left_y;
    body_.setPosition((float)upper_left_x, (float)upper_left_y);
    body_.setSize(sf::Vector2f((float)width_, (float)height_));
    for (auto canvas : canvases_)
        canvas.second->Update(
            upper_left_x + canvas.first.upper_left_x  * width_  / 100,
            upper_left_y + canvas.first.upper_left_y  * height_ / 100,
            upper_left_x + canvas.first.lower_right_x * width_  / 100,
            upper_left_y + canvas.first.lower_right_y * height_ / 100
        );
}

void Canvas::Update(const Vector4f& corners) {
    Update(corners.upper_left_x, corners.upper_left_y, corners.lower_right_x, corners.lower_right_y);
}

void Canvas::Draw(sf::RenderWindow& window) const {
    for (auto drawable : drawables_)
        drawable.second->Draw(window);
    for (auto button : buttons_)
        button.second->Draw(window);
    for (auto canvas : canvases_)
        canvas.second->Draw(window);
}

void Canvas::AddButton(const Vector4f& position, const std::string& texturePath, const Event& action) {
    buttons_.push_back(
        std::pair<Vector4f, Button*>
        (position,
        new Button({
            body_.getPosition().x + position.upper_left_x  * width_  / 100,
            body_.getPosition().y + position.upper_left_y  * height_ / 100,
            body_.getPosition().x + position.lower_right_x * width_  / 100,
            body_.getPosition().y + position.lower_right_y * height_ / 100
        }, texturePath, action))
    );
}

void Canvas::AddDrawable(const Vector4f& position, const std::string& texturePath) {
    drawables_.push_back(
        std::pair<Vector4f, Drawable*>
        (position,
        new Drawable({
            body_.getPosition().x + position.upper_left_x  * width_,
            body_.getPosition().y + position.upper_left_y  * height_,
            body_.getPosition().x + position.lower_right_x * width_,
            body_.getPosition().y + position.lower_right_y * height_
        }, texturePath))
    );
}

void Canvas::AddCanvas(const Vector4f& position) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position,
        new Canvas({
            body_.getPosition().x + position.upper_left_x  * width_,
            body_.getPosition().y + position.upper_left_y  * height_,
            body_.getPosition().x + position.lower_right_x * width_,
            body_.getPosition().y + position.lower_right_y * height_
        }))
    );
}

Vector2f Canvas::GetPosition() {
    return Vector2f({body_.getPosition().x, body_.getPosition().y});
}
