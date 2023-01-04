#include <iostream>
#include <random>
#include "game/Clovece.h"

int main() {

    std::random_device rd;
    std::mt19937 mt(rd());

    auto* clovece = new Clovece(mt);
    auto* p1 = new Player(1);
    auto* p2 = new Player(2);
    auto* p3 = new Player(3);
    auto* p4 = new Player(4);
    clovece->addPlyer(p1);
    clovece->addPlyer(p2);
    clovece->addPlyer(p3);
    clovece->addPlyer(p4);

    clovece->setup();

    while (true) {
        if (!clovece->doTurn()) {
            break;
        }
    }

    std::cout << "" << std::endl;

    delete clovece;
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    return 0;
}
