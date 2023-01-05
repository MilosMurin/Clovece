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
    bool running = false;

public:
    explicit Clovece(std::mt19937 mt);

    void addPlyer(Player* player);

    void setup();

    int rollDice();

    /**
     *
     * @param figure the figure to move
     * @param amount rolled amount
     * @param test true - does not actually move the figure
     * @return true if move is possible
     */
    bool moveFigure(Figure* figure, int amount, bool test);

    void doTurn();

    bool hasMoves(int rolled);

    bool hasMoves(Figure* figure, int rolled);

    bool isHome(Figure* figure);

    bool isHome(Player* player);

    bool isEnd(Figure* figure);

    bool isEnd(Player* player);

    bool isRunning() const;
};
