#include <random>
#include <iostream>
#include "Clovece.h"

using namespace std;

Clovece::Clovece(mt19937 mt) : mt(mt), board(new Board()) {
}

void Clovece::addPlyer(Player* player) {
    int i = 0;
    for (; i < 4; i++) {
        if (players[i] == nullptr) {
            break;
        }
    }
    if (players[i] != nullptr) {
        return;
    }
    if (i == 0) {
        onTurn = player;
    }
    players[i] = player;
}

void Clovece::setup() {
    // set figures to home
    for (auto player : players) {
        for (int i = 0; i < 4; i++) {
            board->getHome(player->getId(), i)->setFigure(player->getFigure(i));
        }
    }
    board->print();
}

int Clovece::rollDice() {
    return dice(mt);
}

/**
 *
 * @param figure the figure to move
 * @param amount rolled amount
 * @param test true - does not actually move the figure
 * @return true if move is possible
 */
bool Clovece::moveFigure(Figure* figure, int amount, bool test) {
    if (!test) {
        std::cout << "  Player is trying to move figure " << figure->getName() << std::endl;
    }
    Circle* start = board->getCircle(figure->getX(), figure->getY());
    Circle* current = start;
    if (board->isHome(start)) { // figure is still home
        if (!test) {
            std::cout << "  Figure is still home" << std::endl;
        }
        if (amount == 6) { // roll was six figure can move out
            current = board->getStart(figure->getPlayer());
        } else {
            if (!test) {
                std::cout << "  Roll wasnt 6 so figure cant go out of home" << std::endl;
            }
            return false; // to move out of home you need to roll 6
        }
    } else {
        for (int i = 0; i < amount; i++) {
            if (current == nullptr) {
                return false; // no space to move to
            }
            current = current->getNext(figure->getPlayer());
        }
    }

    if (current == nullptr) {
        if (!test) {
            std::cout << "  No circle found at that distance" << std::endl;
        }
        return false;
    }
    Figure* fig = current->getFigure();
    if (fig != nullptr) { // circle is occupied
        if (!test) {
            std::cout << "  Circle is occupied";
        }
        if (fig->getPlayer() == figure->getPlayer()) {
            if (!test) {
                std::cout << " by a figure of the same color" << std::endl;
            }
            // unable to move there because it is occupied by a figure with the same color
            return false;
        } else {
            if (!test) {
                std::cout << " by a figure of an opposng color" << std::endl;
            }
            // kick opposing player out
            return false; // return true when fixed
        }
    } else { // circle is empty
        if (!test) {
            std::cout << "  Circle is empty moving figure" << std::endl;
            std::cout << "      from: " << start->getX() << ", " << start->getY() << std::endl;
            std::cout << "      to:   " << current->getX() << ", " << current->getY() << std::endl;
            // move the figure there
            start->setFigure(nullptr);
            current->setFigure(figure);
        }
        return true;
    }
}

bool Clovece::doTurn() {
    std::cout << "Player " << onTurn->getId() << " is on turn." << std::endl;
    int roll = rollDice();
    std::cout << "  Roll was " << roll << std::endl;
    if (hasMoves(roll)) {
        std::cout << "  Choose a figure to move" << std::endl;
        int f = 0;
        cin >> f;
        if (f == -1) {
            return false;
        }
        Figure* figure = onTurn->getFigure(f - 1);
        while (!hasMoves(figure, roll)) {
            std::cout << "  That figure has no moves" << std::endl;
            std::cout << "  Choose a figure to move" << std::endl;
            cin >> f;
            if (f == -1) {
                return false;
            }
        }
        moveFigure(figure, roll, false);
    } else {
        std::cout << "  Player " << onTurn->getId() << " has no moves." << std::endl;
    }
    // set the next player on turn
    int p = onTurn->getId();
    if (p == 4) {
        onTurn = players[0];
    } else {
        onTurn = players[p];
    }
    return true;
}

bool Clovece::hasMoves(int rolled) {
    for (int i = 0; i < 4; i++) {
        Figure* figure = onTurn->getFigure(i);
        if (hasMoves(figure, rolled)) {
            return true;
        }
    }
    return false;
}

bool Clovece::hasMoves(Figure* figure, int rolled) {
    if (board->isHome(board->getCircle(figure->getX(), figure->getY()))) {
        if (rolled == 6) {
            return true;
        }
    } else {
        if (moveFigure(figure, rolled, true)) {
            return true;
        }
    }
    return false;
}
