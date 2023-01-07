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


    std::cout << "Hello welcome to Clovece :)" << std::endl;
    // TODO: Name choosing, figure name choosing

    int game = 0;
    while (game == 0) {
        std::cout << "Would you like to play (1) a singleplayer game or (2) a multiplayer game" << std::endl;
        int s;
        cin >> s;
        if (s > 0 && s < 3) {
            game = s;
        } else {
            std::cout << "That is not a vlid option try typing '1' for singleplayer or '2' for multiplayer" << std::endl;
        }
    }

    if (game == 1) { // singleplayer
        int players = 0;
        while (players == 0) {
            std::cout << "How many players are going to play (1-4) the rest will be filled by bots" << std::endl;
            int s;
            cin >> s;
            if (s > 0 && s < 5) {
                players = s;
            } else {
                std::cout << "That is not a vlid option try typing a number from 1 to 4" << std::endl;
            }
        }
        if (players == 4) { // give choice for bot ids
            for (int i = 1; i <= 4; i++) {
                clovece->getPlayer(i)->setBot(false);
            }
        } else if (players == 3) { // give choice for bot ids
            int bot = 0;
            while (bot == 0) {
                std::cout << "Choose an id that the bot will get (1-4)" << std::endl;
                int s;
                cin >> s;
                if (s > 0 && s < 5) {
                    bot = s;
                } else {
                    std::cout << "That is not a vlid option try typing a number from 1 to 4" << std::endl;
                }
            }
            for (int i = 1; i <= 4; i++) {
                clovece->getPlayer(i)->setBot(bot == i);
            }
        } else { // give choice for player ids
            for (int i = 1; i <= players; i++) {
                int player = 0;
                while (player == 0) {
                    std::cout << "Player " << i << " choose an id you would like have (1-4)" << std::endl;
                    int s;
                    cin >> s;
                    if (s > 0 && s < 5) {
                        if (!clovece->getPlayer(s)->isBot()) {
                            std::cout << "That id is already taken try a different one" << std::endl;
                        } else {
                            player = s;
                        }
                    } else {
                        std::cout << "That is not a vlid option try typing a number from 1 to 4" << std::endl;
                    }
                }
                clovece->getPlayer(player)->setBot(false);
            }
        }
    } else {

    }


    // TODO: Player connection
    clovece->start();

    std::cout << "Ending program" << std::endl;

    delete clovece;
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    return 0;
}
