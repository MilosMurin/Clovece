#pragma once


#include <string>
#include <thread>
#include "Move.h"
#include "../borad/Board.h"
#include "../Player.h"

using namespace std;

class Connection {
private:

    static const int BUFFER_SIZE = 1024;

    bool host;
    string ip;
    unsigned int port;
    bool run = true;

    char buffer[BUFFER_SIZE] = { 0 };

    int socket = 0;

    thread readThread;
    thread writeThread;

    // 2 vlakna jedno na citanie a jedno na zapisovanie

public:
    Connection(bool host, string  ip, unsigned int port);

    void sendString(const char* str);

    void sendMove(Move move);

    void sendEnd();

    void sendBoard(Board* board);

    void sendPlayer(Player* player);

    void readFromSocket();

    void endConnection();
};
