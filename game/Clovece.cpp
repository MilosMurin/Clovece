#include <random>
#include <iostream>
#include "Clovece.h"

using namespace std;

Clovece::Clovece(mt19937 mt) : mt(mt), board(new Board()) {
}

Clovece::~Clovece() {
    delete board;
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
    for (auto player: players) {
        for (int i = 0; i < 4; i++) {
            board->getHome(player->getId(), i)->setFigure(player->getFigure(i));
        }
    }
    running = true;
    board->print();
}

int Clovece::rollDice() {
    return dice(mt);
}

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
            } else {
                std::cout << "--Roll wasnt 6 so figure cant go out of home" << std::endl;
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
        } else {
            std::cout << "--No circle found at that distance" << std::endl;
        }
        return false;
    }
    Figure* fig = current->getFigure();
    if (fig != nullptr) { // circle is occupied
        if (!test) {
            std::cout << "  Circle is occupied";
        } else {
            std::cout << "--Circle is occupied";
        }
        if (fig->getPlayer() == figure->getPlayer()) {
            std::cout << " by a figure of the same color" << std::endl;
            // unable to move there because it is occupied by a figure with the same color
            return false;
        } else {
            std::cout << " by a figure of an opposng color" << std::endl;
            int p = fig->getPlayer();
            Circle* home = board->getHome(p, fig->getId() - 1);
            current->setFigure(nullptr);
            home->setFigure(fig);
            printf("  Figure %d of player %d was kicked by the figure %d of player %d\n",
                   fig->getId(), p, figure->getPlayer(), figure->getId());
        }
    }
    // circle is empty
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

void Clovece::doTurn() {
    std::cout << "Player " << onTurn->getId() << " is on turn." << std::endl;
    // TODO: rolling more times if roll was six
    // TODO: If roll was six player must take out a figure from home and roll again
    int roll = rollDice();
    std::cout << "  Roll was " << roll << std::endl;
    if (isHome(onTurn) && roll != 6) {
        for (int i = 0; i < 2; i++) {
            std::cout << "  Player has all figures home rolling again." << std::endl;
            roll = rollDice();
            std::cout << "  Roll was " << roll << std::endl;
            if (roll == 6) {
                break;
            }
        }
    }
    if (roll == 6) {
        // do a second roll
        // if the player has anyone home he has to get him out (except when start field is occupied)
        // do a return
        // otherwise continue normally
    }
    // if player has any moves make him select (show wich figures can move)


    if (hasMoves(roll)) {
        // move this to a method
        int f = getFigureToMove();
        if (f == -1) {
            return;
        }
        Figure* figure = onTurn->getFigure(f - 1);
        while (!hasMoves(figure, roll)) {
            std::cout << "  Figure" << figure->getId() << " has no moves" << std::endl;
            f = getFigureToMove();
            if (f == -1) {
                return;
            }
            figure = onTurn->getFigure(f - 1);
        }
        moveFigure(figure, roll, false);
        this->board->print();
    } else {
        std::cout << "  Player " << onTurn->getId() << " has no moves." << std::endl;
    }
    if (isEnd(onTurn)) {
        running = false;
        std::cout << "Player " << onTurn->getId() << " won the game" << std::endl;
        return;
    }
    // set the next player on turn
    int p = onTurn->getId();
    if (p == 4) {
        onTurn = players[0];
    } else {
        onTurn = players[p];
    }
}

int Clovece::getFigureToMove() {
    std::cout << "  Choose a figure to move" << std::endl;
    int f = 0;
    cin >> f;
    if (f == -1) {
        running = false;
        return f;
    }
    while (f > 4 || f < 0) {
        std::cout << "  Invalid figure id. Try again." << std::endl;
        cin >> f;
        if (f == -1) {
            running = false;
            return f;
        }
    }
    return f;
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
    if (isHome(figure)) {
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

bool Clovece::isHome(Figure* figure) {
    return board->isHome(board->getCircle(figure->getX(), figure->getY()));
}

bool Clovece::isHome(Player* player) {
    for (int i = 0; i < 4; i++) {
        Figure* figure = player->getFigure(i);
        if (!isHome(figure)) {
            return false;
        }
    }
    return true;
}

bool Clovece::isEnd(Figure* figure) {
    return board->isEnd(figure->getPlayer(), board->getCircle(figure->getX(), figure->getY()));
}

bool Clovece::isEnd(Player* player) {
    for (int i = 0; i < 4; i++) {
        Figure* figure = player->getFigure(i);
        if (!isEnd(figure)) {
            return false;
        }
    }
    return true;
}

bool Clovece::isRunning() const {
    return running;
}
