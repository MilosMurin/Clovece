#ifndef CLOVECE_SETTINGS_H
#define CLOVECE_SETTINGS_H
#endif //CLOVECE_SETTINGS_H

#include <iostream>
#include <fstream>

class Settings{
private:
    std::fstream settingsFile;
    int width;
    int height;

public:
    Settings();

    ~Settings();

    int getWidth();

    int getHeight();

    void openSettingsFile();

    void closeSettingsFile();

    std::string getSettings();

    void setSettings(std::string screenSize);

    void setScreenSize(std::string screenSize);
};