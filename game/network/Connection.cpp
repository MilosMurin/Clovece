#include "Connection.h"

#include <utility>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

Connection::Connection(bool host, string  ip, unsigned int port) : host(host), ip(std::move(ip)), port(port) {

}

void Connection::sendString(const char* str) {
    if (strlen(str) >= BUFFER_SIZE) {
        return;
    }
    send(socket, str, strlen(str), 0);
}

void Connection::sendMove(Move move) {
    sendString(reinterpret_cast<const char*>(move.toWeb()));
// TODO: :)
}

void Connection::sendEnd() {
    sendString(":end:");
}

void Connection::sendBoard(Board* board) {

}

void Connection::sendPlayer(Player* player) {

}

void Connection::readFromSocket() {
    while (run) {

        read(socket, buffer, BUFFER_SIZE);

    }
}

void Connection::endConnection() {
    run = false;
}
