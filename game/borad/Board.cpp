#include <iostream>
#include "Board.h"

Board::Board() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            auto* c = new Circle(default1[i][j]);
            c->setPosition(i, j);
            board[i][j] = c;
            int p = c->getPlayer();
            if (p > 0) {
                int k = 0;
                switch (c->getFunction()) {
                    case EMPTY:
                        break;
                    case HOME:
                        while (homes[p - 1][k] != nullptr) {
                            k++;
                        }
                        homes[p - 1][k] = c;
                        break;
                    case START:
                        starts[p - 1] = c;
                        break;
                    case END:
                        while (ends[p - 1][k] != nullptr) {
                            k++;
                        }
                        ends[p - 1][k] = c;
                        break;
                }
            }
        }
    }
    Circle* last = nullptr;
    for (auto i: defaultCon) {
        if (last != nullptr) {
            last->setNext(board[i[0]][i[1]]);
        }
        last = board[i[0]][i[1]];
    }

    for (auto& item : defaultEnds) {
        Circle* before = nullptr;
        for (auto& subItem : item) {
            if (before != nullptr) {
                before->setNext(board[subItem[0]][subItem[1]]);
            }
            before = board[subItem[0]][subItem[1]];
        }
    }
}

Board::~Board() {
    for (auto& i: board) {
        for (auto& item: i) {
            delete item;
        }
    }
}

void Board::print() {
    for (auto& i: board) {
        for (int j = 1; j < 4; j++) {
            for (auto& k: i) {
                std::cout << k->getLine(j);
            }
            std::cout << std::endl;
        }
    }
}

Circle* Board::getStart(int player) {
    return starts[player - 1];
}

Circle* Board::getCircle(int x, int y) {
    return board[x][y];
}

Circle* Board::getHome(int player, int id) {
    return homes[player - 1][id];
}

bool Board::isHome(Circle* circle) {
    for (auto& home: homes) {
        for (auto& j: home) {
            if (j == circle) {
                return true;
            }
        }
    }
    return false;
}
