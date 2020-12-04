#include "state.hpp"

State::State(const std::string& state_name)
    : state_name_(state_name) { }

State::~State() {
    for (auto canvas : canvases_)
        delete canvas.second;
}

Event State::EventHandler(const sf::Event& sf_event) {
    Event event;
    switch (sf_event.type) {
        case sf::Event::Closed:
            OnResize(sf_event.size.width, sf_event.size.height);
            break;
        case sf::Event::Resized:
            OnResize(sf_event.size.width, sf_event.size.height);
            for (auto canvas : canvases_)
                canvas.second->Update({
                    canvas.first.upper_left_x  * width_  / 100,
                    canvas.first.upper_left_y  * height_ / 100,
                    canvas.first.lower_right_x * width_  / 100,
                    canvas.first.lower_right_y * height_ / 100,
                });
            break;
        case sf::Event::MouseMoved:
            OnMouseMovement(sf_event.mouseMove.x, sf_event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            event = OnClick(sf_event.mouseButton.x, sf_event.mouseButton.y);
            break;
        default:
            break;
    }
    return event;
}

void State::OnResize(int x, int y) {
    width_ = x;
    height_ = y;
}

void State::OnMouseMovement(int x, int y) {
    Vector2f relative = {
        100.0f * x / width_,
        100.0f * y / height_
    };
    for (auto canvas : canvases_) {
        if (canvas.first.upper_left_x < relative.x &&
            relative.x < canvas.first.lower_right_x &&
            canvas.first.upper_left_y < relative.y &&
            relative.y < canvas.first.lower_right_y) {
                Event e(EventType::MouseMovement);
                e.coords = {(short)x, (short)y};
                canvas.second->EventHandler(e);
        }
    }
}

Event State::OnClick(int x, int y) {
    Event event;
    Vector2f relative = {
        100.0f * x / width_,
        100.0f * y / height_
    };
    for (auto canvas : canvases_) {
        if (canvas.first.upper_left_x < relative.x &&
            relative.x < canvas.first.lower_right_x &&
            canvas.first.upper_left_y < relative.y &&
            relative.y < canvas.first.lower_right_y) {
                Event e(EventType::MouseClick);
                e.coords = {(short)x, (short)y};
                event = canvas.second->EventHandler(e);
        }
        if (event.type != EventType::None)
            return event;
    }
    return event;
}

void State::Draw(sf::RenderWindow& window) {
    for (auto canvas : canvases_)
        canvas.second->Draw(window);
}

const std::string& State::GetName() const {
    return state_name_;
}

void State::AddCanvas(const Vector4f& position) {
    canvases_.push_back(
        std::pair<Vector4f, Canvas*>
        (position,
        new Canvas({
            position.upper_left_x * WINDOW_WIDTH / 100,
            position.upper_left_y * WINDOW_HEIGHT / 100,
            position.lower_right_x * WINDOW_WIDTH / 100,
            position.lower_right_y * WINDOW_HEIGHT / 100
        }))
    );
}
