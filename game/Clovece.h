#pragma once

#include "borad/Board.h"
#include "Player.h"

class Clovece {

private:
    Board* board;
    Player* players[4]{};
    Player* onTurn = nullptr;
    std::mt19937 mt;
    uniform_int_distribution<int> dice{1, 6};

public:
    explicit Clovece(std::mt19937 mt);

    void addPlyer(Player* player);

    void setup();

    int rollDice();

    bool moveFigure(Figure* figure, int amount, bool test);

    bool doTurn();

    bool hasMoves(int rolled);

    bool hasMoves(Figure* figure, int rolled);
};
