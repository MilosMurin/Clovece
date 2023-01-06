#pragma once
#ifndef CLOVECE_GRAPHIC_H
#define CLOVECE_GRAPHIC_H
#endif //CLOVECE_GRAPHIC_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Settings.h"

class Graphic {
private:
    sf::RenderWindow *currentWindow;
    sf::RenderWindow *subWindow;
    Settings settings;
public:
    Graphic();

    ~Graphic();

    void createWindow(std::string windowName);

};