#include "Graphic.h"

Graphic::Graphic() {
    currentWindow = nullptr;
    subWindow = nullptr;
}

Graphic::~Graphic() {
    delete currentWindow;
    delete subWindow;
}

void Graphic::createWindow(std::string windowName) {
    sf::RenderWindow window(sf::VideoMode(settings.getWidth(), settings.getHeight()), windowName, sf::Style::Default);
    window.clear(sf::Color::White);
    window.setPosition(sf::Vector2i(20,20));
}
