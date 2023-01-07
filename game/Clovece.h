#pragma once

#include "borad/Board.h"
#include "Player.h"
#include "network/Move.h"
#include "network/Connection.h"

class Clovece {

private:
    Board* board;
    Player* players[4]{};
    Player* onTurn = nullptr;
    std::mt19937 mt;
    uniform_int_distribution<int> dice{1, 6};
    bool running = false;
    int playerId = 1;
    Connection* connection = nullptr;

public:
    explicit Clovece(std::mt19937 mt);

    ~Clovece();

    void addPlyer(Player* player);

    void setup();

    void start();

    int rollDice();

    void print();

    void nameBots();

    /**
     * @param figure the figure to move
     * @param amount rolled amount
     * @param test true - does not actually move the figure
     * @return true if move is possible
     */
    bool moveFigure(Figure* figure, int amount, bool test);

    bool moveFigure(Move move);

    /**
     * @param bot if true it automatically chooses the first figure that can move, if false it lets the player choose through console
     */
    int getFigureToMove(int roll);

    void doTurn();

    bool hasMoves(int rolled);

    bool hasMoves(Figure* figure, int rolled);

    bool isHome(Figure* figure);

    bool isHome(Player* player);

    bool isEnd(Figure* figure);

    bool isEnd(Player* player);

    bool isRunning() const;

    Figure* getFigure(Move move);

    int getPlayerId() const;

    void setPlayerId(int playerId);

    void nextPlayerOnTurn();

    Player* getPlayer(int id);

    Connection* getConnection() const;

    void setConnection(Connection* connection);
};
