#include "state.hpp"
#include "../map/map.hpp"

State::State(const std::string& state_name, int width, int height)
    : state_name_(state_name), width_(width), height_(height) {

}

State::~State() {
    for (auto canvas : canvases_)
        delete canvas.second;
}

Event State::EventHandler(double d_time, const sf::Event& sf_event) {
    Event event;
    Vector2f relative;
    switch (sf_event.type) {
        case sf::Event::Resized:
            OnResize(sf_event.size.width, sf_event.size.height);
            break;
        case sf::Event::MouseMoved:
            OnMouseMovement(sf_event.mouseMove.x, sf_event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            event = OnClick(sf_event.mouseButton.x, sf_event.mouseButton.y);
            event = CustomOnClick(event);
            break;
        case sf::Event::MouseButtonReleased:
            relative = {
                (float)(sf_event.mouseButton.x) / width_,
                (float)(sf_event.mouseButton.y) / height_
            };
            event.type = EventType::MouseClickReleased;
            event.body = {relative.x, relative.y};
            event = CustomOnClick(event);
        default:
            break;
    }
    Update(d_time);
    return event;
}

void State::Draw(sf::RenderWindow& window) {
    for (auto canvas : canvases_)
        canvas.second->Draw(window);
}

void State::Update(double d_time) {

}

void State::OnResize(int x, int y) {
    width_ = x;
    height_ = y;
}

void State::OnMouseMovement(int x, int y) {
    Vector2f relative = {
        (float)x / width_,
        (float)y / height_
    };
    for (auto canvas : canvases_) {
        if (
            canvas.first.upper_left_x  < relative.x &&
            canvas.first.lower_right_x > relative.x &&
            canvas.first.upper_left_y  < relative.y &&
            canvas.first.lower_right_y > relative.y
            ) {
            Event event(EventType::MouseMovement);
            event.body = {relative.x, relative.y};
            canvas.second->EventHandler(event);
        }
    }
}

Event State::OnClick(int x, int y) {
    Event event;
    Vector2f relative = {
        (float)x / width_,
        (float)y / height_
    };
    for (auto canvas : canvases_) {
        if (
            canvas.first.upper_left_x  < relative.x &&
            canvas.first.lower_right_x > relative.x &&
            canvas.first.upper_left_y  < relative.y &&
            canvas.first.lower_right_y > relative.y
            ) {
            event.type = EventType::MouseClick;
            event.body = {relative.x, relative.y};
            event = canvas.second->EventHandler(event);
        }
        if (event.type != EventType::None)
            return event;
    }
    return event;
}

Event State::CustomOnClick(Event event) {
    return event;
}

void State::AddCanvas(const Vector4f& position) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position, new Canvas(position))
    );
}

void State::AddCanvas(const Vector4f& position, const std::string& mapPath) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position, new Map(position, mapPath))
    );
}

void State::AddCanvas(const Vector4f& position, int width, int height) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position, new Map(position, width, height))
    );
}

const std::string& State::GetName() const {
    return state_name_;
}
