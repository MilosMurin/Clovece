#pragma once


#include "board/Figure.h"

using namespace std;

class Player {

private:
    Figure* figures[4]{};
    // color
    std::string name;
    int id;
    bool bot = true;
    bool online = false;

public:
    explicit Player(int id);
    Player(int id, std::string name);
    ~Player();

    const string& getName() const;

    int getId() const;

    Figure* getFigure(int i);

    string toWeb() const;

    void loadFromWeb(const string& str);

    bool isBot() const;

    void setBot(bool bot);

    bool isOnline() const;

    void setIsOnline(bool online);

    void setName(const string& name);
};
