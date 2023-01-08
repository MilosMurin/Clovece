#include <unistd.h>
#include "Graphic.h"


Graphic::Graphic(std::string windowName) {
    window.setTitle(windowName);

    window.setPosition(sf::Vector2i(20,20));
    auto width = settings.getWidth();
    auto heigh = settings.getWidth();
    window.setSize(sf::Vector2u(width,heigh));
    window.clear(sf::Color::White);



    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...

        // end the current frame
        window.display();
    }
}

Settings* Graphic::getSettings() {
    return &settings;
}

void Graphic::drawIntoWindow() {
    for (int i = 0; i < drawCount; ++i) {
        window.draw(*draw[i]);
    }

}

void Graphic::addDrawableSprite(std::string what, int posX, int posY, int size, int color) {
    std::string path = "../graphic/icons/";
    auto *sprite = new sf::Sprite();
    auto *texture = new sf::Texture();
    texture->loadFromFile(path);
    sprite->setPosition(posX, posY);
    sprite->setScale(size, size);

    //figures
    if (what == "figure") {
        switch (color) {

                //yellow
            case 1:
                path += "figure_yellow.png";
                texture->loadFromFile(path);
                break;

                //blue
            case 2:
                path += "figure_blue.png";
                texture->loadFromFile(path);
                break;

                //green
            case 3:
                path += "figure_green.png";
                texture->loadFromFile(path);
                break;

                //red
            case 4:
                path += "figure_red.png";
                texture->loadFromFile(path);
                break;
        }
    } else if (what == "home"){
        switch (color) {

            //yellow
            case 1:
                path += "circle_yellow_home.png";
                texture->loadFromFile(path);
                break;

                //blue
            case 2:
                path += "circle_blue_home.png";
                texture->loadFromFile(path);
                break;

                //green
            case 3:
                path += "circle_green_home.png";
                texture->loadFromFile(path);
                break;

                //red
            case 4:
                path += "circle_red_home.png";
                texture->loadFromFile(path);
                break;
        }
    } else if(what == "start"){
        switch (color) {

            //yellow
            case 1:
                path += "circle_yellow_start.png";
                texture->loadFromFile(path);
                break;

                //blue
            case 2:
                path += "circle_blue_start.png";
                texture->loadFromFile(path);
                break;

                //green
            case 3:
                path += "circle_green_start.png";
                texture->loadFromFile(path);
                break;

                //red
            case 4:
                path += "circle_red_start.png";
                texture->loadFromFile(path);
                break;
        }
    } else if (what == "path"){
        path += "circle_path.png";
        texture->loadFromFile(path);
    }

    draw[drawCount] = sprite;
    drawCount++;
}


