#include "graphic/Graphic.h"

int client() {
    auto* graphic = new Graphic();
    graphic->createWindow("Nove okno");

    auto* settings = new Settings();
    std::cout << settings->getHeight();
    return 0;
}