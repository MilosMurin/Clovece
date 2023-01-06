#include "Connection.h"

#include <utility>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

Connection::Connection(bool host, string  ip, unsigned int port) : host(host), ip(std::move(ip)), port(port) {

    if (host) {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
//            printError("Chyba - socket.");
        }

        //definovanie adresy servera <arpa/inet.h>
        struct sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;         //internetove sockety
        serverAddress.sin_addr.s_addr = INADDR_ANY; //prijimame spojenia z celeho internetu
        serverAddress.sin_port = htons(port);       //nastavenie portu

        //prepojenie adresy servera so socketom <sys/socket.h>
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
//            printError("Chyba - bind.");
        }

        //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
        listen(serverSocket, 10);

        for (int& client : sockets) {
            //server caka na pripojenie klienta <sys/client.h>
            struct sockaddr_in clientAddress{};
            socklen_t clientAddressLength = sizeof(clientAddress);
            client = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
            // TODO: Allow for host to stop accepting at any time
            if (client < 0) {
//                printError("Chyba - accept.");
            }
        }


        //uzavretie pasivneho socketu <unistd.h>
        close(serverSocket);

    } else {
        //ziskanie adresy a portu servera <netdb.h>
        struct hostent* server = gethostbyname(this->ip.c_str());
        if (server == nullptr) {
//            printError("Server neexistuje.");
        }

        //vytvorenie socketu <sys/socket.h>
        comSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (comSocket < 0) {
//            printError("Chyba - socket.");
        }

        //definovanie adresy servera <arpa/inet.h>
        struct sockaddr_in serverAddress{};
        bzero((char*) &serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        bcopy((char*) server->h_addr, (char*) &serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(port);

        if (connect(comSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
//            printError("Chyba - connect.");
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
    for (int socket : sockets) {
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
        read(comSocket, buffer, BUFFER_SIZE);
        if (strcmp(buffer, ":end:") == 0) {
            run = false;
        } else {
            // TODO: play the move
        }
    }
}

void Connection::endConnection() {
    run = false;
}
