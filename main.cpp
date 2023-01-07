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
        std::cout << "Would you like to play [1] a singleplayer game or [2] a multiplayer game" << std::endl;
        string str;
        cin >> str;
        int s = atoi(str.c_str());
        if (s > 0 && s < 3) {
            game = s;
        } else {
            std::cout << "That is not a vlid option try typing '1' for singleplayer or '2' for multiplayer" << std::endl;
        }
    }

    if (game == 1) { // singleplayer
        int players = 0;
        while (players == 0) {
            std::cout << "How many players are going to play [1-4] the rest will be filled by bots" << std::endl;
            string str;
            cin >> str;
            int s = atoi(str.c_str());
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
                std::cout << "Choose an id that the bot will get [1-4]" << std::endl;
                string str;
                cin >> str;
                int s = atoi(str.c_str());
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
                    std::cout << "Player " << i << " choose an id you would like have [1-4]" << std::endl;
                    string str;
                    cin >> str;
                    int s = atoi(str.c_str());
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
        int host = 0;
        while (host == 0) {
            std::cout << "Would you like to [1] host the game or [2] join someones game" << std::endl;
            string str;
            cin >> str;
            int s = atoi(str.c_str());
            if (s > 0 && s < 3) {
                host = s;
            } else {
                std::cout << "That is not a vlid option try typing '1' for hosting a game or '2' for joining a game" << std::endl;
            }
        }
        if (host == 1) {
            bool cont = true;
            while (cont) {
                int port = 0;
                while (port == 0) {
                    std::cout << "Choose a port to open the game on (more than 0)" << std::endl;
                    string str;
                    cin >> str;
                    int s = atoi(str.c_str());
                    if (s > 0) {
                        port = s;
                    } else {
                        std::cout << "That is not a vlid option try typing a number higher than 0" << std::endl;
                    }
                }
                std::cout << "Send your address to people you want to connect to with the port you have chosen"
                          << std::endl;

                auto* con = new Connection(true, "", port);
                if (con->isConnected() > 1) {
                    //
                } else {
                    std::cout << "Nobody connected. Try again? [Y/N]" << std::endl;
                    string s2;
                    cin >> s2;
                    if (s2 == "N") {
                        cont = false;
                    }
                }
            }

        } else {
            bool connected = false;
            while (!connected) {
                std::cout << "Write the address to connect to (without the port)" << std::endl;
                string address;
                if (address == "-1") {
                    break;
                }
                cin >> address;
                std::cout << "Write the port to connect to" << std::endl;
                int port;
                cin >> port;
                auto* con = new Connection(false, address, port);
                if (con->isConnected() == 1) {
                    clovece->setConnection(con);
                    connected = true;
                } else {
                    std::cout << "Connection failed! Try again, or type -1 to end the program." << std::endl;
                    delete con;
                }
            }
        }
    }

    clovece->start();

    std::cout << "Ending program" << std::endl;

    delete clovece;
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    return 0;
}
