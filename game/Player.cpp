#include "Player.h"

#include <utility>
#include <sstream>


Player::Player(int id) : Player(id, "Player " + to_string(id)) {

}

Player::Player(int id, std::string name) : id(id), name(std::move(name)) {
    for (int i = 0; i < 4; i++) {
        figures[i] = new Figure(i + 1, this->name + "`s figure " + to_string(i + 1), id);
    }
}

Player::~Player() {
    for (auto& figure: figures) {
        delete figure;
    }
}


const string& Player::getName() const {
    return name;
}

int Player::getId() const {
    return id;
}

Figure* Player::getFigure(int i) {
    return figures[i];
}

string Player::toWeb() const{
    string s = this->name;
    for (auto& figure: figures) {
        s += "|" + figure->toWeb();
    }
    s += "|";
    return s;
}

void Player::loadFromWeb(const string& str) {
    stringstream strstr{str};
    getline(strstr, this->name, '|');
    for (auto& figure: figures) {
        string s;
        getline(strstr, s, '|');
        figure->loadFromWeb(s);
    }
}
