#include <SFML/Graphics.hpp>
#include "game/app.hpp"
#include "utils/app_constants.hpp"

int main()
{
    App app(WINDOW_HEIGHT, WINDOW_WIDTH);
    app.Run();
}