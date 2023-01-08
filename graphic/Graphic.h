#pragma once
#ifndef CLOVECE_GRAPHIC_H
#define CLOVECE_GRAPHIC_H
#endif //CLOVECE_GRAPHIC_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Settings.h"

class Graphic {
private:
    Settings settings;
    sf::RenderWindow window;
    sf::Drawable* draw[100];
    int drawCount = 0;
public:
    Graphic(std::string windowName);

    ~Graphic();

    Settings* getSettings();

    void drawIntoWindow();

    void addDrawableSprite(std::string path, int posX, int posY, int size, int color);

};