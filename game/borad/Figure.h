#pragma once

#include <string>

using namespace std;

class Figure {

private:
    // color
    string name;
    int player;
    int id;
    int x;
    int y;

public:
    Figure(int id, string name, int player);

    /**
     * Player ids are 1-4
     * @return player id that owns this figure
     */
    int getPlayer() const;

    const string& getName() const;

    void setName(const string& name);

    void setCircle(int x, int y);

    int getX() const;

    int getY() const;

    /**
     * Figure ids are 1-4
     * @return the id of this figure
     */
    int getId() const;
};
