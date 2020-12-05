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
    State(const std::string& state_name, int width, int height);
    ~State();
    virtual Event       EventHandler(double d_time, const sf::Event& sf_event);
    virtual void        OnResize(int x, int y);
    virtual void        OnMouseMovement(int x, int y);
    virtual Event       OnClick(int x, int y);
    void                Draw(sf::RenderWindow& window);
    const std::string&  GetName() const;
protected:
    void                AddCanvas(const Vector4f& position);
    void                AddMap(const Vector4f& position, const std::string& mapPath);
    void                AddBlankMap(const Vector4f& position, int width, int height);
    Canvases            canvases_;
    int                 width_;
    int                 height_;
private:
    std::string         state_name_;
};
