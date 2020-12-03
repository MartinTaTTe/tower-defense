#include "gui_manager.hpp"

GUIManager::GUIManager() {

}

GUIManager::~GUIManager() {
    for (auto canvas : canvases_)
        delete canvas;
}
