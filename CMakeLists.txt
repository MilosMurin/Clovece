cmake_minimum_required(VERSION 3.18)
project(Clovece)

set(CMAKE_CXX_STANDARD 14)

add_executable(Clovece main.cpp
        game/borad/Board.cpp game/borad/Board.h
        game/borad/Circle.cpp game/borad/Circle.h
        game/borad/Figure.cpp game/borad/Figure.h
        game/Clovece.cpp game/Clovece.h
        game/Player.cpp game/Player.h
        game/network/Move.cpp game/network/Move.h
        game/network/Connection.cpp game/network/Connection.h
        Client/graphic/Graphic.cpp
        Client/graphic/Graphic.h
        Client/graphic/Settings.cpp
        Client/graphic/Settings.h
        Client/client.cpp)

#LOCAL SFML
#pridať cestu k suboru, aby sme ju nemuseli meniť vždy keď to presunieme inam
set(SFML “C:\\Users\\jgres\\Desktop\\Princípy operačných systémov\\SP POS\\Človeče”)
find_package(SFML REQUIRED COMPONENTS graphics system)

#find_package(SFML REQUIRED COMPONENTS graphics system)
#include_directories("usr/include/SFML")
target_link_libraries(Clovece sfml-graphics sfml-window)
