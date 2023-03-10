#include "Figure.h"

#include <utility>

Figure::Figure(int id, string name, int player) : id(id), name(std::move(name)), player(player) {

}

const string& Figure::getName() const {
    return name;
}

void Figure::setName(const string& name) {
    Figure::name = name;
}

int Figure::getPlayer() const {
    return player;
}

int Figure::getX() const {
    return x;
}

int Figure::getY() const {
    return y;
}

void Figure::setCircle(int x, int y) {
    this->x = x;
    this->y = y;
}

int Figure::getId() const {
    return id;
}

string Figure::toWeb() {
    return to_string(this->id) + this->name;
}

void Figure::loadFromWeb(const string& str) {
    this->id = str[0] - 48;
    this->name = str.substr(1);
}
