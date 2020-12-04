#include "canvas.hpp"

Canvas::Canvas(const Vector4i& body) {
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
    Event return_event;
    Vector2f relative;
    switch (event.type)
    {
    case EventType::Resize:
        Update({
            event.body.upper_left_x,
            event.body.upper_left_y,
            event.body.lower_right_x,
            event.body.lower_right_y
        });
        break;
    case EventType::MouseMovement:
        relative.x = (float)(event.coords.x - body_.getPosition().x) / width_;
        relative.y = (float)(event.coords.y - body_.getPosition().y) / height_;
        for (auto button : buttons_) {
            if (button.first.upper_left_x < relative.x && relative.x < button.first.lower_right_x &&
                button.first.upper_left_y < relative.y && relative.y < button.first.lower_right_y)
                button.second->Highlight(true);
            else
                button.second->Highlight(false);
        }
        break;
    case EventType::MouseClick:
        relative.x = (float)(event.coords.x - body_.getPosition().x) / width_;
        relative.y = (float)(event.coords.y - body_.getPosition().y) / height_;
        for (auto button : buttons_) {
            if (button.first.upper_left_x < relative.x && relative.x < button.first.lower_right_x &&
                button.first.upper_left_y < relative.y && relative.y < button.first.lower_right_y)
                return_event = button.second->Press(true);
        }
        break;
    default:
        break;
    }
    return return_event;
}

void Canvas::Update(const Vector4i& corners) {
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
            (int)(position.upper_left_x * width_)   + (int)body_.getPosition().x,
            (int)(position.upper_left_y * height_)  + (int)body_.getPosition().y,
            (int)(position.lower_right_x * width_)  + (int)body_.getPosition().x,
            (int)(position.lower_right_y * height_) + (int)body_.getPosition().y
        }, texturePath, action))
    );
}

void Canvas::AddDrawable(const Vector4f& position, const std::string& texturePath) {
    drawables_.push_back(
        std::pair<Vector4f, Drawable*>
        (position,
        new Drawable({
            (int)(position.upper_left_x * width_)   + (int)body_.getPosition().x,
            (int)(position.upper_left_y * height_)  + (int)body_.getPosition().y,
            (int)(position.lower_right_x * width_)  + (int)body_.getPosition().x,
            (int)(position.lower_right_y * height_) + (int)body_.getPosition().y
        }, texturePath))
    );
}

void Canvas::AddCanvas(const Vector4f& position) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position,
        new Canvas({
            (int)(position.upper_left_x * width_)   + (int)body_.getPosition().x,
            (int)(position.upper_left_y * height_)  + (int)body_.getPosition().y,
            (int)(position.lower_right_x * width_)  + (int)body_.getPosition().x,
            (int)(position.lower_right_y * height_) + (int)body_.getPosition().y
        }))
    );
}

Vector2i Canvas::GetPosition() {
    return {(int)body_.getPosition().x, (int)body_.getPosition().y};
}

void Canvas::Update(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y) {
    width_  = lower_right_x - upper_left_x;
    height_ = lower_right_y - upper_left_y;
    body_.setPosition((float)upper_left_x, (float)upper_left_y);
    body_.setSize(sf::Vector2f((float)width_, (float)height_));
    for (auto canvas : canvases_)
        canvas.second->Update(
            upper_left_x + canvas.first.upper_left_x  * width_,
            upper_left_y + canvas.first.upper_left_y  * height_,
            upper_left_x + canvas.first.lower_right_x * width_,
            upper_left_y + canvas.first.lower_right_y * height_
        );
}
