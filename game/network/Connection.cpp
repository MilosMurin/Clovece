#include "Connection.h"

#include <utility>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <csignal>

Connection::Connection(bool host, string ip, unsigned int port) :
        host(host), ip(std::move(ip)), port(port), mutexRun(new mutex()), mutexRead(new mutex()),
        mutexWrite(new mutex()), writeMove(new condition_variable()), playMove(new condition_variable()),
        writeMoveToSend(new condition_variable()), sendMoveCond(new condition_variable()) {

    if (this->host) {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            std::cout << "Nastala chyba pri vytvarani socketu" << std::endl;
            return;
        }

        struct sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(this->port);


        if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
            std::cout << "Nastala chyba pri bindovani socketu" << std::endl;
            return;
        }

        listen(serverSocket, 10);

        for (int i = 0; i < 4; i++) {
            bool connected = false;
            bool cont = true;
            while (!connected) {
                struct sockaddr_in clientAddress{};
                socklen_t clientAddressLength = sizeof(clientAddress);
                sockets[i] = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressLength);
                std::cout << "A player wants to connect to your game do you accept them? [Y/N]" << std::endl;
                string s;
                cin >> s;
                if (s == "N") {
                    close(sockets[i]);
                } else {
                    connected = true;
                    send(sockets[i], to_string(idToSend++).c_str(), 1, 0);
                }
                if (sockets[i] < 0) {
                    std::cout << "Nastala chyba pri spojeni" << std::endl;
                }
                if (i < 3) {
                    std::cout << "Do you want to continue accepting players? [Y/N]" << std::endl;
                    string s2;
                    cin >> s2;
                    if (s2 == "N") {
                        cont = false;
                    }
                }
            }
            if (!cont) {
                break;
            }
        }

        close(serverSocket);

    } else {
        //ziskanie adresy a portu servera <netdb.h>
        struct hostent* server = gethostbyname(this->ip.c_str());
        if (server == nullptr) {
            std::cout << "Server neexistuje" << std::endl;
            return;
        }

        //vytvorenie socketu <sys/socket.h>
        comSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (comSocket < 0) {
            std::cout << "Nastala chyba pri vytvarani socketu" << std::endl;
            return;
        }

        //definovanie adresy servera <arpa/inet.h>
        struct sockaddr_in serverAddress{};
        bzero((char*) &serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        bcopy((char*) server->h_addr, (char*) &serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(this->port);

        if (connect(comSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
            std::cout << "Nastala chyba pri pripajani" << std::endl;
            return;
        }
    }
    readThread = new thread([this]() -> void { this->readFromSocket(); });
    writeThread = new thread([this]() -> void { this->sendString(); });
}

Connection::~Connection() {
    delete mutexRun;
    delete mutexRead;
    delete mutexWrite;
    delete writeMove;
    delete playMove;
    delete writeMoveToSend;
    delete sendMoveCond;
}

void Connection::writeStringToSend(string str) {
    std::unique_lock<std::mutex> loc(*mutexWrite);
    while (toSend != "-") {
//        std::cout << "Still unsend string present" << std::endl;
        writeMoveToSend->wait(loc);
    }
    toSend = std::move(str);
    sendMoveCond->notify_one();
    loc.unlock();
}

void Connection::sendString() {
    signal(SIGPIPE, nullptr);
    bool runWrite = true;
    while (runWrite) {
        std::unique_lock<std::mutex> loc(*mutexWrite);
        while (toSend == "-") {
//            std::cout << "Nothing to send" << std::endl;
            sendMoveCond->wait(loc);
        }
        if (toSend.length() < BUFFER_SIZE) {
            if (comSocket > 0) {
                send(comSocket, toSend.c_str(), toSend.length(), 0);
            }
            for (int socket: sockets) {
                if (socket > 0) {
                    send(socket, toSend.c_str(), toSend.length(), 0);
                }
            }
        }
        toSend = "-";
        writeMoveToSend->notify_one();
        std::unique_lock<std::mutex> loc2(*mutexRun);
        runWrite = run;
        loc2.unlock();
    }
    if (comSocket > 0) {
        send(comSocket, "end", strlen("end"), 0);
    }
    for (int socket: sockets) {
        if (socket > 0) {
            send(socket, "end", strlen("end"), 0);
        }
    }
    if (comSocket > 0) {
        close(comSocket);
    }
    for (int socket: sockets) {
        if (socket > 0) {
            close(socket);
        }
    }
}

void Connection::sendMove(Move* move) {
    writeStringToSend(to_string(move->toWeb()));
}

void Connection::sendEnd() {
    writeStringToSend("end");
}

void Connection::sendPlayer(Player* player) {
    writeStringToSend(player->toWeb());
}

void Connection::readFromSocket() {
    signal(SIGPIPE, nullptr);
    bool runRead = true;
    while (runRead) {
        if (host) {
            for (int socket: sockets) {
                if (socket > 0) {
                    read(socket, buffer, BUFFER_SIZE);
                    readString(buffer);
                }
            }
        } else {
            if (comSocket > 0) {
                read(comSocket, buffer, BUFFER_SIZE);
                readString(buffer);
            }
        }
        std::unique_lock<std::mutex> loc(*mutexRun);
        runRead = run;
        loc.unlock();
    }
}

void Connection::readString(const char* str) {
    if (strcmp(str, "end") == 0) {
        endConnection();
    } else {
        std::unique_lock<std::mutex> loc(*mutexRead);
        while (received != "-") {
//            std::cout << "Still unplayed move present" << std::endl;
            writeMove->wait(loc);
        }
        received = str;
        playMove->notify_one();
        loc.unlock();
    }
}

void Connection::endConnection() {
    std::unique_lock<std::mutex> loc(*mutexRun);
    run = false;
    loc.unlock();
}

int Connection::isConnected() {
    if (host) {
        int counter = 0;
        for (int socket: sockets) {
            if (socket > 0) {
                counter++;
            }
        }
        return counter;
    } else {
        if (comSocket > 0) {
            return 1;
        }
        return 0;
    }
}

const string& Connection::getReceived() const {
    return received;
}

mutex* Connection::getMutexRead() const {
    return mutexRead;
}

condition_variable* Connection::getWriteMove() const {
    return writeMove;
}

condition_variable* Connection::getPlayMove() const {
    return playMove;
}

bool Connection::isHost() const {
    return host;
}

void Connection::setReceived(const string& received) {
    this->received = received;
}

bool Connection::shouldRun() {
    return run;
}

Response::Response() = default;

Response::Response(const string& value) {
    setValue(value);
}

bool Response::isMove() const {
    if (isInt) {
        if (intValue >= 1001 && intValue <= 4412) {
            return true;
        }
    }
    return false;
}

bool Response::isNum() const {
    return isInt;
}

int Response::getIntValue() const {
    return intValue;
}

const string& Response::getValue() const {
    return value;
}

void Response::setValue(const string& value) {
    this->value = value;
    try {
        intValue = stoi(this->value);
    } catch (exception& e) {
        isInt = false;
    }
}

bool Response::isEnd() {
    return this->value == "end";
}
