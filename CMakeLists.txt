cmake_minimum_required(VERSION 3.18)
project(Clovece)

set(CMAKE_CXX_STANDARD 14)

#SERVER CMAKE
set(SOURCE
        game/borad/Board.cpp
        game/borad/Circle.cpp
        ame/borad/Figure.cpp
        game/Clovece.cpp
        game/Player.cpp
        game/network/Move.cpp
        game/network/Connection.cpp
    )
set(HEADERS
        game/borad/Board.h
        game/borad/Circle.h
        game/borad/Figure.h
        game/Clovece.h
        game/Player.h
        game/network/Move.h
        game/network/Connection.h
        )
add_executable(Clovece main.cpp)

#FRIOS SFML
#find_package(SFML REQUIRED COMPONENTS graphics system)
#include_directories("usr/include/SFML")
#target_link_libraries(Clovece sfml-graphics sfml-window)

#CLIENT CMAKE
set(SOURCE
        Client/graphic/Graphic.cpp
        Client/graphic/Settings.cpp
        )
set(HEADERS
        Client/graphic/Graphic.h
        Client/graphic/Settings.h
        )
add_executable(Client Client/client.cpp)

#LOCAL SFML
set(SFML_DIR "C:\\Users\\jgres\\Desktop\\Princípy operačných systémov\\SP POS\\Človeče\\SFML\\lib\\cmake\\SFML")
set(SFML_STATIC_LIBRARIES TRUE)
include_directories("C:/SFML/include")

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Clovece sfml-system sfml-window sfml-graphics sfml-audio sfml-network)