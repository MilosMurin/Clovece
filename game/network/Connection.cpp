#include "Connection.h"

#include <utility>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

Connection::Connection(bool host, string ip, unsigned int port) : host(host), ip(std::move(ip)), port(port) {

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
}

void Connection::sendString(const char* str) const {
    if (strlen(str) >= BUFFER_SIZE) {
        return;
    }
    if (comSocket > 0) {
        send(comSocket, str, strlen(str), 0);
    }
    for (int socket: sockets) {
        if (socket > 0) {
            send(socket, str, strlen(str), 0);
        }
    }
}

void Connection::sendMove(Move* move) const {
    sendString(to_string(move->toWeb()).c_str());
}

void Connection::sendEnd() const {
    sendString(":end:");
}

void Connection::sendPlayer(Player* player) const {
    sendString(player->toWeb().c_str());
}

void Connection::readFromSocket() {
    while (run) {
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
    }
}

void Connection::readString(const char* str) {
    if (strcmp(str, "end") == 0) {
        run = false;
    } else {
        // TODO: play the move
        // lock mutex board
        // play the move
        // unlock mutex
    }
}

void Connection::endConnection() {
    run = false;
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
