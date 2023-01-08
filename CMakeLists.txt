cmake_minimum_required(VERSION 3.18)
project(Clovece)

set(CMAKE_CXX_STANDARD 14)

add_executable(Clovece main.cpp
        game/board/Board.cpp game/board/Board.h
        game/board/Circle.cpp game/board/Circle.h
        game/board/Figure.cpp game/board/Figure.h
        game/Clovece.cpp game/Clovece.h
        game/Player.cpp game/Player.h
        game/network/Move.cpp game/network/Move.h
        game/network/Connection.cpp game/network/Connection.h
        )

target_link_libraries(Clovece pthread)
