#pragma once
/*
Canvases are used to manage Drawables and Buttons in a certain area.
*/
#include <vector>

#include "button.hpp"
#include "../utils/event.hpp"
#include "../utils/app_constants.hpp"

class Canvas;
typedef std::vector<std::pair<Vector4f, Canvas*>> Canvases;
typedef std::vector<std::pair<Vector4f, Button*>> Buttons;
typedef std::vector<std::pair<Vector4f, Drawable*>> Drawables;
typedef std::vector<std::pair<Vector2f, sf::Text>> Texts;

class Canvas {
public:
    Canvas(const Vector4f& body);
    ~Canvas();
    virtual Event       EventHandler(const Event& event);
    void                Draw(sf::RenderWindow& window) const;
    virtual void        CustomDraw(sf::RenderWindow& window) const;
    void                AddButton(const Vector4f& position, const std::string& texturePath = T_DEFAULT_BUTTON, const Event& action = Event());
    void                AddDrawable(const Vector4f& position, const std::string& texturePath);
    void                AddCanvas(const Vector4f& position);
    void                AddText(const Vector2f& position, const std::string& string, int font_size = 20, sf::Color color = sf::Color::Black);
    void                UpdateString(int i, const std::string& string);
protected:
    Canvases            canvases_;
    Buttons             buttons_;
    Drawables           drawables_;
    Texts               texts_;
    Vector4f            body_;
private:
    sf::Font            font_;
};
