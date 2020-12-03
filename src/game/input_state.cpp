#include "input_state.hpp"
#include "mapeditor_state.hpp"
#include <iostream>

InputState::InputState()
    : State("Input State"), string_("Enter map size in form of YxY. Example 5x5. Max size is 9x9") {
        text_.setString(string_);
        font_.loadFromFile("./utils/OpenSans.ttf");
        playerText_.setFont(font_);
        playerText_.setFillColor(sf::Color::Black);
        
     }

Event InputState::EventHandler(const sf::Event& sf_event) {
    Event event(EventType::None);
    switch (sf_event.type) {
        case sf::Event::TextEntered:
            if (sf_event.text.unicode < 128)
                playerInput_ +=sf_event.text.unicode;
                playerText_.setString(playerInput_);
            break;
        case sf::Event::MouseButtonPressed:
            event.type = EventType::MouseClick;
            event.coords.x = sf_event.mouseButton.x;
            event.coords.y = sf_event.mouseButton.y;
            if(event.coords.x >= WINDOW_WIDTH/2 - 100 && event.coords.x <= WINDOW_WIDTH/2 - 25) {
                if(event.coords.y >= WINDOW_HEIGHT/2 + 50 && event.coords.y <= WINDOW_HEIGHT/2 + 75) {
                    playerInput_ = "";
                    playerText_.setString(playerInput_);
                }
            }
            if(event.coords.x >= WINDOW_WIDTH/2 +25 && event.coords.x <= WINDOW_WIDTH/2 + 50) {
                if(event.coords.y >= WINDOW_HEIGHT/2 + 50 && event.coords.y <= WINDOW_HEIGHT/2 + 75) {
                    if(isdigit(playerInput_[0]) && isdigit(playerInput_[2]) && playerInput_[1] == 'x' && !sizeGot_) {
                        width_ = playerInput_[0] - '0';
                        height_ = playerInput_[2] - '0';
                        // Vector2i size;
                        // size.x = WINDOW_WIDTH;
                        // size.y = WINDOW_HEIGHT;
                        // return new MapEditorState(size, width, height, "jeff");
                        sizeGot_ = true;
                        string_ = "Enter map name";
                        text_.setString(string_);
                        playerInput_ = "";
                        playerText_.setString(playerInput_);
                    } else if (sizeGot_ && !playerInput_.empty()) {
                        std::string name = playerInput_;
                        Vector2i size;
                        size.x = WINDOW_WIDTH;
                        size.y = WINDOW_HEIGHT;
                        event.type = EventType(PushState);
                        event.state = new MapEditorState(size, width_, height_, name);
                    }
                }
            }
            break;
    }           
    return event;
}


void InputState::Draw(sf::RenderWindow& window) {
    sf::RectangleShape background((sf::Vector2f)window.getSize());
    sf::RectangleShape inputBox(sf::Vector2f(200, 50));
    sf::RectangleShape resetBox(sf::Vector2f(75, 25));
    sf::RectangleShape startBox(sf::Vector2f(75, 25));
    sf::Text reset;
    sf::Text start;
    reset.setString("RESET");
    start.setString("START");
    text_.setFont(font_);
    text_.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 250, WINDOW_HEIGHT/2 - 75));
    text_.setFillColor(sf::Color::Black);
    text_.setCharacterSize(20);
    playerText_.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 25));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 25));
    inputBox.setOutlineThickness(10.0f);
    resetBox.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 50));
    resetBox.setFillColor(sf::Color::White);
    resetBox.setOutlineColor(sf::Color::Black);
    resetBox.setOutlineThickness(10.0f);
    reset.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 50));
    reset.setFont(font_);
    reset.setFillColor(sf::Color::Black);
    reset.setCharacterSize(10);
    start.setPosition(sf::Vector2f(WINDOW_WIDTH/2 + 25, WINDOW_HEIGHT/2 + 50));
    start.setFont(font_);
    start.setFillColor(sf::Color::Black);
    start.setCharacterSize(10);
    startBox.setPosition(sf::Vector2f(WINDOW_WIDTH/2 + 25, WINDOW_HEIGHT/2 + 50));
    startBox.setFillColor(sf::Color::White);
    startBox.setOutlineColor(sf::Color::Black);
    startBox.setOutlineThickness(10.0f);
    window.draw(background);
    window.draw(text_);
    window.draw(inputBox);
    window.draw(playerText_);
    window.draw(resetBox);
    window.draw(reset);
    window.draw(startBox);
    window.draw(start);
}