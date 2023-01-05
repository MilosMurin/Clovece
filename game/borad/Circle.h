#pragma once
#include <stdexcept>
#include "Figure.h"

enum Type {
    NOTHING, // 0 // Filler circle
    NUETRAL, // 1 // playable empty circle
    P_ONE, // 2 // player one colored circle
    P_TWO, // 3 // ...
    P_THREE, // 4
    P_FOUR // 5
    // if needed add more players, names are color neutral for color customization
};

enum Function {
    EMPTY, // 0 // no function circle
    HOME, // 1 // home circles
    START, // 2 // starting circle, after leaving home
    END // 3 // ending circles
};

enum Special {
    // for powerups
};

class Circle {

private:
    Type type;
    Function function;
    Figure* figure = nullptr;
    Circle* next = nullptr;
    Circle* toHome = nullptr; // is set only if it points to a home of a player
    int x = -1;
    int y = -1;

public:
    Circle();
    explicit Circle(int num);
    Circle(Type type, Function special);
    ~Circle();

    Type getType() const;

    Function getFunction() const;

    Figure* getFigure() const;

    void setFigure(Figure* newFigure);

    bool hasFigure() const;

    void setNext(Circle* circle);

    Circle* getNext(int player);

    int getPlayer();

    void setPosition(int x, int y);

    int getX() const;

    int getY() const;

    string getLine(int index);
};
