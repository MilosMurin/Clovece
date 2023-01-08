#include "Settings.h"
#include <iostream>

Settings::Settings() {
    //readSettings();
    width = 600;
    height = 600;
}

Settings::~Settings() {

}

int Settings::getWidth() {
    return width;
}

int Settings::getHeight() {
    return height;
}

void Settings::writeSettings() {
    std::ofstream settingsFileWrite;
    settingsFileWrite.clear();
    settingsFileWrite << width << "x" << height;
    settingsFileWrite.close();
}

void Settings::readSettings() {
    std::ifstream settingsFileRead;
    settingsFileRead.open("../graphic/Settings.txt");

    std::string x = "";
    std::string y = "";
    std::string screenSize = "";
    bool secondSize = false;
    settingsFileRead >> screenSize;

    for (int i = 0; i < screenSize.length(); ++i) {
        if(screenSize.at(i) != 'x') {
            x += screenSize.at(i);
        } else {
            secondSize = true;
        }
        if (secondSize)
            y += screenSize.at(i);
    }
    width = stoi(x);
    height = stoi(y);
}

