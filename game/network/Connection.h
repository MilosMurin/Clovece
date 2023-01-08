#pragma once


#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Move.h"
#include "../borad/Board.h"
#include "../Player.h"

using namespace std;

class Connection {
private:

    static const int BUFFER_SIZE = 1024;
    int idToSend = 2;

    bool host;
    string ip;
    unsigned int port;
    bool run = true;
    mutex* mutexRun;

    char buffer[BUFFER_SIZE] = { 0 };

    int comSocket = 0;
    int sockets[4]{};

    thread* readThread;
    thread* writeThread;

    string received = "-";
    mutex* mutexRead;
    condition_variable* writeMove;
    condition_variable* playMove;

    string toSend = "-";
    mutex* mutexWrite;
    condition_variable* writeMoveToSend;
    condition_variable* sendMoveCond;

    string name;
    string names[5];

    // 2 vlakna jedno na citanie a jedno na zapisovanie

public:
    Connection(bool host, string  ip, unsigned int port);

    ~Connection();

    void sendString();

    void sendMove(Move* move);

    void sendEnd();

    void readFromSocket();

    void readString(const char* str);

    void endConnection();

    int isConnected();

    void writeStringToSend(string str);

    const string& getReceived() const;

    mutex* getMutexRead() const;

    condition_variable* getWriteMove() const;

    condition_variable* getPlayMove() const;

    bool isHost() const;

    void setReceived(const string& received);

    bool shouldRun() const;

    void setName(const string& name);

    const string& getName(int i) const;
};

class Response {

    string value;
    int intValue = 0;
    bool isInt = true;

public:
    Response();
    explicit Response(const string& value);

    bool isMove() const;

    bool isEnd();

    bool isNum() const;

    const string& getValue() const;

    int getIntValue() const;

    void setValue(const string& value);
};
