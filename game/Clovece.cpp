#include <random>
#include <iostream>
#include "Clovece.h"
#include <sstream>

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
}

void Clovece::start() {
    running = true;
    while (running) {
        doTurn();
        if (!connection->shouldRun()) {
            running = false;
        }
    }
    connection->getReadThread()->join();
    connection->getWriteThread()->join();
}

int Clovece::rollDice() {
    return dice(mt);
}

bool Clovece::moveFigure(Figure* figure, int amount, bool test) {
    if (!test) {
        std::cout << "\t" << onTurn->getName() << " is trying to move figure " << figure->getName() << std::endl;
    }
    Circle* start = board->getCircle(figure->getX(), figure->getY());
    Circle* current = start;
    if (board->isHome(start)) { // figure is still home
        if (!test) {
            std::cout << "  Figure is still home" << std::endl;
        }
        if (amount >= 6) { // roll was six figure can move out
            current = board->getStart(figure->getPlayer());
            amount -= 6;
        } else {
            if (!test) {
                std::cout << "  Roll wasnt 6 so figure cant go out of home" << std::endl;
            }
            return false; // to move out of home you need to roll 6
        }
    }

    for (int i = 0; i < amount; i++) {
        if (current == nullptr) {
            return false; // no space to move to
        }
        current = current->getNext(figure->getPlayer());
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
                int p = fig->getPlayer();
                Circle* home = board->getHome(p, fig->getId() - 1);
                current->setFigure(nullptr);
                home->setFigure(fig);
                printf("  Figure %d of player %d was kicked by the figure %d of player %d\n",
                       fig->getId(), p, figure->getPlayer(), figure->getId());
            }
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
    if (onTurn->isBot()) {
        chrono::seconds sec(1);
        this_thread::sleep_for(sec);
    }
    Move move;
    std::cout << onTurn->getName() << " is on turn." << std::endl;
    if (onTurn->isOnline()) {
        std::cout << onTurn->getName() << " is an online player." << std::endl;

        Response response{};
        while (!response.isMove()) {
            std::unique_lock<std::mutex> loc(*connection->getMutexRead());
            while (connection->getReceived() == "-") {
                std::cout << "Waiting for player to choose a figure to move" << std::endl;
                connection->getPlayMove()->wait(loc);
            }
            response.setValue(connection->getReceived());
            connection->setReceived("-");
            connection->getWriteMove()->notify_one();
            loc.unlock();
//            std::cout << "Received: [" << response.getValue() << "]" << std::endl;

            if (response.isMove()) {
//                std::cout << response.getIntValue() << std::endl;
                Move movePtr{response.getIntValue()};
                moveFigure(movePtr);
            } else if (response.isEnd() || response.getValue().empty()) {
                if (connection->isHost()) {
                    std::cout << "Player has disconnected!" << std::endl;
                } else {
                    std::cout << "Host has ended the game!" << std::endl;
                }
                running = false;
                break;
            }
        }
    } else {
        this->print();
        std::cout << onTurn->getName() << " is a local player." << std::endl;
        int roll = rollDice();
        std::cout << "\tRoll was " << roll << std::endl;
        if (isHome(onTurn) && roll != 6) {
            for (int i = 0; i < 2; i++) {
                std::cout << "\t" << onTurn->getName() << " has all figures home rolling again." << std::endl;
                roll = rollDice();
                std::cout << "\tRoll was " << roll << ", total is " << roll << std::endl;
                if (roll == 6) {
                    break;
                }
            }
        }
        if (roll == 6) {
            // do a second roll
            std::cout << "\tSince roll was 6 rolling again" << std::endl;
            int roll2 = rollDice();
            roll += roll2;
            std::cout << "\tRoll was " << roll2 << ", total is " << roll << std::endl;
        }
        // if player has any moves make him select (show wich figures can move)
        if (hasMoves(roll)) {
            // move this to a method
            int f = getFigureToMove(roll);
            if (f == -1) {
                return;
            }
            Figure* figure = onTurn->getFigure(f - 1);
            while (!hasMoves(figure, roll)) {
                std::cout << "\tFigure" << figure->getId() << " has no moves" << std::endl;
                f = getFigureToMove(roll);
                if (f == -1) {
                    return;
                }
                figure = onTurn->getFigure(f - 1);
            }
            move = {onTurn->getId(), figure->getId(), roll};
            moveFigure(figure, roll, false);
            this->print();
        } else {
            std::cout << "\t" << onTurn->getName() << " has no moves." << std::endl;
            move = {onTurn->getId(), 0, roll};
        }
        if (isEnd(onTurn)) {
            running = false;
            std::cout << "\t" << onTurn->getName() << " won the game" << std::endl;
            return;
        }
        if (connection != nullptr) {
            connection->sendMove(&move);
        }
        // set the next player on turn
        nextPlayerOnTurn();
    }
}

int Clovece::getFigureToMove(int roll) {
    int f = 0;
    if (onTurn->isBot()) {
        for (int i = 0; i < 4; i++) {
            if (hasMoves(onTurn->getFigure(i), roll)) {
                f = i + 1;
                break;
            }
        }
    } else {
        std::cout << "\tChoose a figure to move [";
        for (int i = 0; i < 4; i++) {
            if (hasMoves(onTurn->getFigure(i), roll))
                cout << onTurn->getFigure(i)->getId();
            int ableToMove = 0;
            for (int j = 0; j < 4; j++) {
                if (hasMoves(onTurn->getFigure(j), roll))
                    ableToMove++;
            }
            if (i < 3 && hasMoves(onTurn->getFigure(i), roll)) {
                if (ableToMove != 1)
                    cout << " ";
            }
        }
        cout << "]" << std::endl;
        cin >> f;
        if (f == -1) {
            running = false;
            return f;
        }
        while (f > 4 || f <= 0) {
            std::cout << "\tInvalid figure id. Try again." << std::endl;
            cin >> f;
            if (f == -1) {
                running = false;
                return f;
            }
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
        if (rolled >= 6) {
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
            if (!isEnd(figure)) {
                return false;
            }
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

Figure* Clovece::getFigure(Move move) {
    return players[move.getPlayerId() - 1]->getFigure(move.getFigureId() - 1);
}

bool Clovece::moveFigure(Move move) {
    bool res = true;
    if (move.getFigureId() != 0) {
        res = moveFigure(getFigure(move), move.getRolled(), false);
    }
    nextPlayerOnTurn();
    return res;
}

int Clovece::getPlayerId() const {
    return playerId;
}

void Clovece::setPlayerId(int playerId) {
    Clovece::playerId = playerId;
}

void Clovece::nextPlayerOnTurn() {
    int p = onTurn->getId();
    if (p == 4) {
        onTurn = players[0];
    } else {
        onTurn = players[p];
    }
}

Player* Clovece::getPlayer(int id) {
    return players[id - 1];
}

Connection* Clovece::getConnection() const {
    return connection;
}

void Clovece::setConnection(Connection* connection) {
    this->connection = connection;
}

void Clovece::print() {
    char p1[30];
    char p2[30];
    char p3[30];
    char p4[30];
    sprintf(p1, "%-27s", ("[" + players[0]->getName() + "]").c_str());
    sprintf(p2, "%27s", ("[" + players[1]->getName() + "]").c_str());
    sprintf(p3, "%-27s", ("[" + players[2]->getName() + "]").c_str());
    sprintf(p4, "%27s", ("[" + players[3]->getName() + "]").c_str());
    cout << p1 << p2 << endl;
    board->print();
    cout << p3 << p4 << endl;
}

void Clovece::nameBots() {
    for (auto player: players) {
        if (player->isBot())
            player->setName("AI " + to_string(player->getId()));
    }
}

void Clovece::loadPlayersFromWeb(string str) {
    stringstream strstr{str};
    for (auto& player: players) {
        string s;
        getline(strstr, s, ';');
        if (player->getId() != playerId) {
            player->loadFromWeb(s);
        }
    }
}

string Clovece::playersToWeb() {
    string s;
    for (auto& player: players) {
        s += player->toWeb() + ";";
    }
    return s;
}
