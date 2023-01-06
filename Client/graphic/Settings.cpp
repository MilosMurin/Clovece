#include "Settings.h"

Settings::Settings() {
    openSettingsFile();
    std::string screenSize;
    while(!settingsFile.eof()){
        settingsFile >> screenSize;
    }

    if(screenSize.length() > 3){
        width = 600;
        height = 600;
        setSettings(std::to_string(width) + "x" + std::to_string(height));
    } else {
        setScreenSize(screenSize);
    }
}

Settings::~Settings() {

}

void Settings::openSettingsFile() {
    settingsFile.open("Client\\graphic\\Settings.txt");
}

void Settings::closeSettingsFile() {
    settingsFile.close();
}

std::string Settings::getSettings() {
    openSettingsFile();
    std::string screenSize = "";
    settingsFile >> screenSize;
    closeSettingsFile();
    return screenSize;
}

void Settings::setSettings(std::string screenSize) {
    openSettingsFile();
    settingsFile.clear();
    settingsFile << screenSize;
    closeSettingsFile();
}

void Settings::setScreenSize(std::string screenSize) {
    std::string x = "";
    std::string y = "";
    bool secondSize = false;

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

int Settings::getWidth() {
    return width;
}

int Settings::getHeight() {
    return height;
}

