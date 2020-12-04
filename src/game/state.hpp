#pragma once
/*
Base class.
A State manages everything that is currently happening, from graphics to logic.
*/
#include <SFML/Graphics.hpp>

#include "../utils/event.hpp"
#include "../gui/canvas.hpp"

typedef std::vector<std::pair<Vector4f, Canvas*>> Canvases;

class State {
public:
    State(const std::string& state_name);
    ~State();
    virtual Event       EventHandler(const sf::Event& sf_event);
    void                OnResize(int x, int y);
    void                OnMouseMovement(int x, int y);
    Event               OnClick(int x, int y);
    void                Draw(sf::RenderWindow& window);
    const std::string&  GetName() const;
protected:
    void                AddCanvas(const Vector4f& body);
    Canvases            canvases_;
    int                 width_;
    int                 height_;
private:
    std::string         state_name_;
};
