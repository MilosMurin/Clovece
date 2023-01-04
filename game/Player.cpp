#include "Player.h"

#include <utility>


Player::Player(int id) : Player(id, "Player " + to_string(id)) {

}

Player::Player(int id, std::string name) : id(id), name(std::move(name)) {
    for (int i = 0; i < 4; i++) {
        figures[i] = new Figure(i + 1, this->name + "`s figure " + to_string(i + 1), id);
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
