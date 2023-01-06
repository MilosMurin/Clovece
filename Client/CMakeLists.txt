cmake_minimum_required(VERSION 3.18)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client Client/client.cpp
        Client/graphic/Graphic.cpp
        Client/graphic/Graphic.h
        Client/graphic/Settings.cpp
        Client/graphic/Settings.h)

#LOCAL SFML
#pridať cestu k suboru, aby sme ju nemuseli meniť vždy keď to presunieme inam
#set(SFML “C:\\Users\\jgres\\Desktop\\Princípy operačných systémov\\SP POS\\Človeče”)
#find_package(SFML REQUIRED COMPONENTS graphics system)

find_package(SFML REQUIRED COMPONENTS graphics system)
include_directories("usr/include/SFML")
target_link_libraries(Clovece sfml-graphics sfml-window)
