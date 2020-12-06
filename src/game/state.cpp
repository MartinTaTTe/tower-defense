#include "state.hpp"
#include "../map/map.hpp"
#include <windows.h>

State::State(const std::string& state_name, int width, int height)
    : state_name_(state_name), width_(width), height_(height) {

}

State::~State() {
    for (auto canvas : canvases_)
        delete canvas.second;
}

Event State::EventHandler(double d_time, const sf::Event& sf_event) {
    Event event;
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
            Sleep(100);
            break;
        case sf::Event::MouseButtonReleased:
            event.type = EventType::MouseClickReleased;
            event.x = sf_event.mouseButton.x;
            event.y = sf_event.mouseButton.y;
            event = CustomOnClick(event);
            Sleep(100);
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
    for (auto canvas : canvases_)
        canvas.second->Update({
            (int)(canvas.first.upper_left_x * width_),
            (int)(canvas.first.upper_left_y * height_),
            (int)(canvas.first.lower_right_x * width_),
            (int)(canvas.first.lower_right_y * height_)
        });
}

void State::OnMouseMovement(int x, int y) {
    Vector2f relative = {
        (float)x / width_,
        (float)y / height_
    };
    for (auto canvas : canvases_) {
        if (canvas.first.upper_left_x < relative.x &&
            relative.x < canvas.first.lower_right_x &&
            canvas.first.upper_left_y < relative.y &&
            relative.y < canvas.first.lower_right_y) {
                Event e(EventType::MouseMovement);
                e.coords = {x, y};
                canvas.second->EventHandler(e);
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
        if (canvas.first.upper_left_x < relative.x &&
            relative.x < canvas.first.lower_right_x &&
            canvas.first.upper_left_y < relative.y &&
            relative.y < canvas.first.lower_right_y) {
                Event e(EventType::MouseClick);
                e.coords = {x, y};
                event = canvas.second->EventHandler(e);
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
        (position,
        new Canvas({
            (int)(position.upper_left_x * width_),
            (int)(position.upper_left_y * height_),
            (int)(position.lower_right_x * width_),
            (int)(position.lower_right_y * height_)
        }))
    );
}

void State::AddCanvas(const Vector4f& position, const std::string& mapPath) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position,
        new Map({
            (int)(position.upper_left_x * width_),
            (int)(position.upper_left_y * height_),
            (int)(position.lower_right_x * width_),
            (int)(position.lower_right_y * height_)
        }, mapPath))
    );
}

void State::AddCanvas(const Vector4f& position, int width, int height) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position,
        new Map({
            (int)(position.upper_left_x * width_),
            (int)(position.upper_left_y * height_),
            (int)(position.lower_right_x * width_),
            (int)(position.lower_right_y * height_)
        }, width, height))
    );
}

const std::string& State::GetName() const {
    return state_name_;
}
