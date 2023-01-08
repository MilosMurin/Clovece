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
        graphic/Graphic.h graphic/Graphic.cpp
        graphic/Settings.h graphic/Settings.cpp
        debug_leaks/debug_new.h debug_leaks/debug_new.cpp
        debug_leaks/_nvwa.h
        debug_leaks/fast_mutex.h
        debug_leaks/c++_features.h
        )


#FRIOS SFML
find_package(SFML REQUIRED COMPONENTS graphics system)
include_directories("usr/include/SFML")
target_link_libraries(Clovece sfml-graphics sfml-window)

target_link_libraries(Clovece pthread)
