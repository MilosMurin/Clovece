#include <iostream>
#include <random>
#include "game/Clovece.h"

string getName(const string& prefix);

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

    // TODO: Name sending

    int game = 0;
    while (game == 0) {
        std::cout << "Would you like to play [1] a singleplayer game or [2] a multiplayer game" << std::endl;
        string str;
        cin >> str;
        int s;
        if (str == "s" || str == "singleplayer") {
            s = 1;
        } else if (str == "m" || str == "multiplayer") {
            s = 2;
        } else {
            s = atoi(str.c_str());
        }
        if (s > 0 && s < 3) {
            game = s;
        } else {
            std::cout << "That is not a vlid option try typing '1' for singleplayer or '2' for multiplayer"
                      << std::endl;
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
                std::string name = getName("Player " + to_string(i));
                clovece->getPlayer(i)->setName(name);
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
                if (bot != i) {
                    std::string name = getName("Player " + to_string(i));
                    clovece->getPlayer(i)->setName(name);
                }
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
                std::string name = getName("Player " + to_string(i));
                clovece->getPlayer(player)->setName(name);
            }
        }
    } else {
        std::string name = getName("");

        int host = 0;
        while (host == 0) {
            std::cout << "Would you like to [1] host the game or [2] join someones game" << std::endl;
            string str;
            cin >> str;
            int s;
            if (str == "h" || str == "host") {
                s = 1;
            } else if (str == "j" || str == "join") {
                s = 2;
            } else {
                s = atoi(str.c_str());
            }
            if (s > 0 && s < 3) {
                host = s;
            } else {
                std::cout << "That is not a vlid option try typing '1' for hosting a game or '2' for joining a game"
                          << std::endl;
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
                if (con->isConnected() >= 1) {
                    clovece->setConnection(con);
                    clovece->getPlayer(1)->setBot(false);
                    for (int i = 2; i <= 1 + con->isConnected(); i++) {
                        clovece->getPlayer(i)->setBot(false);
                        clovece->getPlayer(i)->setIsOnline(true);
                        clovece->getPlayer(i)->setName(con->getName(i));
                    }
                    cont = false;
                    con->writeStringToSend(clovece->playersToWeb());
                } else {
                    std::cout << "Nobody connected. Try again? [Y/N]" << std::endl;
                    string s2;
                    cin >> s2;
                    if (s2 == "N" || s2 == "n" || s2 == "no" || s2 == "No") {
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
                    for (int i = 1; i <= 4; i++) {
                        clovece->getPlayer(i)->setBot(false);
                        clovece->getPlayer(i)->setIsOnline(true);
                    }
                    int id = -1;
                    while (id == -1) {
                        Response response{};
                        std::unique_lock<std::mutex> loc(*con->getMutexRead());
                        while (con->getReceived() == "-") {
                            std::cout << "Waiting for host to send your id" << std::endl;
                            con->getPlayMove()->wait(loc);
                        }
                        response.setValue(con->getReceived());
                        con->getWriteMove()->notify_one();
                        loc.unlock();
                        if (response.isNum()) {
                            if (response.getIntValue() <= 4) {
                                id = response.getIntValue();
                                std::cout << "Received id: " << id << std::endl;
                                clovece->setPlayerId(id);
                                clovece->getPlayer(id)->setIsOnline(false);
                                clovece->getPlayer(id)->setName(name);
                                con->setReceived("-");
                            }
                        }
                    }
                    Response response{};
                    std::unique_lock<std::mutex> loc(*con->getMutexRead());
                    while (con->getReceived() == "-") {
                        std::cout << "Waiting for host to start the game" << std::endl;
                        con->getPlayMove()->wait(loc);
                    }
                    response.setValue(con->getReceived());
                    con->getWriteMove()->notify_one();
                    loc.unlock();
                    clovece->loadPlayersFromWeb(response.getValue());
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


string getName(const string& prefix) {
    std::string name;
    while (name.empty()) {
        if (!prefix.empty()) {
            std::cout << "Chose your name" << std::endl;
        } else {
            std::cout << prefix << " chose your name" << std::endl;
        }
        cin >> name;
        if (name.empty()) {
            std::cout << "Name cannot be empty" << std::endl;
        } else if (name.find('|') != -1 && name.find(';') != -1 && name.find(',') != -1 &&
                name.find('/') != -1 && name.find('\\') != -1) {
            std::cout << "Name cannot contain any special symbol" << std::endl;
            name = "";
        } else if (name.length() > 20) {
            std::cout << "Name cannot be longer than 20 characters" << std::endl;
            name = "";
        }
    }
    return name;
}
