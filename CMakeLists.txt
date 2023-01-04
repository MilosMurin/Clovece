cmake_minimum_required(VERSION 3.18)
project(Clovece)

set(CMAKE_CXX_STANDARD 14)

add_executable(Clovece main.cpp
        game/borad/Board.cpp game/borad/Board.h
        game/borad/Circle.cpp game/borad/Circle.h
        game/borad/Figure.cpp game/borad/Figure.h
        game/Clovece.cpp game/Clovece.h
        game/Player.cpp game/Player.h
        )
