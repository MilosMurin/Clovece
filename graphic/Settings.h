#ifndef CLOVECE_SETTINGS_H
#define CLOVECE_SETTINGS_H
#endif //CLOVECE_SETTINGS_H

#include <iostream>
#include <fstream>

class Settings{
private:
    int width;
    int height;

public:
    Settings();

    ~Settings();

    int getWidth();

    int getHeight();

    void writeSettings();

    void readSettings();
};