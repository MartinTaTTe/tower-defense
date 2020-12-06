#pragma once
/*
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
    Event               EventHandler(double d_time, const sf::Event& sf_event);
    void                Draw(sf::RenderWindow& window);
    const std::string&  GetName() const;
protected:
    virtual void        Update(double d_time);
    virtual void        OnResize(int x, int y);
    virtual void        OnMouseMovement(int x, int y);
    Event               OnClick(int x, int y);
    virtual Event       CustomOnClick(Event event);
    void                AddCanvas(const Vector4f& position);
    void                AddCanvas(const Vector4f& position, const std::string& mapPath);
    void                AddCanvas(const Vector4f& position, int width, int height);
    Canvases            canvases_;
    int                 width_;
    int                 height_;
private:
    std::string         state_name_;
};
